#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <mach/hardware.h>

#include <plat/regs-adc.h>
#include <mach/ts.h>
#include <mach/irqs.h>

static struct input_dev *TouchDev;

struct TouchRegs
{
    unsigned long ADCCON;
    unsigned long ADCTSC;
    unsigned long ADCDLY;
    unsigned long ADCDAT0;
    unsigned long ADCDAT1;
    unsigned long ADCUPDN;
    unsigned long ADCCLRINT;
    unsigned long ADCRESERVE;
    unsigned long ADCCLRINTPNDNUP;
};

struct TouchRegs *TouchRegs;
#define TouchRegsStartAddr 0x7E00B000
struct clk *TPClk;
static struct timer_list LongPressTimer;

static void StartGetPosition()
{
    TouchRegs->ADCTSC = (1 << 3) | (1 << 2);
}

static void StartAD()
{
    TouchRegs->ADCCON |= (1 << 0);
}

static void WaitInterrupt()
{
    TouchRegs->ADCTSC = 0xd3;     //wait interrupt
}

/**************************************************
 * AD转换中断函数
 * @param irq
 * @param dev_id
 * @return
 *************************************************/
static irqreturn_t ADIRQ(int irq, void *dev_id)
{
    static int XVal[4];
    static int YVal[4];
    static int cnt = 0;
    static X_Ver, Y_Ver;

    XVal[cnt] = TouchRegs->ADCDAT0 & 0xFFF;
    YVal[cnt] = TouchRegs->ADCDAT1 & 0xFFF;
    if((TouchRegs->ADCDAT0 & (1 << 15)) != 0 && (TouchRegs->ADCDAT1 & (1 << 15)) != 0)
    {
        cnt = 0;
        input_report_abs(TouchDev, ABS_PRESSURE, 0);
        input_report_key(TouchDev, BTN_TOUCH, 0);
        input_sync(TouchDev);
        WaitInterrupt();
    }
    else
    {
        if(cnt >= 3)
        {
            cnt = 0;
            X_Ver = (XVal[0] + XVal[1] + XVal[2] + XVal[3])>>2;
            Y_Ver = (YVal[0] + YVal[1] + YVal[2] + YVal[3])>>2;
            input_report_abs(TouchDev, ABS_X, X_Ver);
            input_report_abs(TouchDev, ABS_Y, Y_Ver);
            input_report_abs(TouchDev, ABS_PRESSURE, 1);
            input_report_key(TouchDev, BTN_TOUCH, 1);
            input_sync(TouchDev);

            //启动定时器，处理滑动操作
            mod_timer(&LongPressTimer, jiffies + HZ/100);
            WaitInterrupt();
        }
        else
        {
            ++cnt;
            StartGetPosition();
            StartAD();
        }
    }

    TouchRegs->ADCCLRINT = 0x77;      //clear flag

    return 0;
}

static irqreturn_t TouchIRQ(int irq, void *dev_id)
{
    if((TouchRegs->ADCDAT0 & (1 << 15)) != 0 && (TouchRegs->ADCDAT1 & (1 << 15)) != 0)       //up interrupt
    {
        input_report_abs(TouchDev, ABS_PRESSURE, 0);
        input_report_key(TouchDev, BTN_TOUCH, 0);
        input_sync(TouchDev);
        WaitInterrupt();
        TouchRegs->ADCCLRINTPNDNUP = 0x77;      //clear flag
    }
    else if((TouchRegs->ADCDAT0 & (1 << 15)) == 0 && (TouchRegs->ADCDAT1 & (1 << 15)) == 0)
    {
        StartGetPosition();
        StartAD();
        TouchRegs->ADCCLRINTPNDNUP = 0x77;      //clear flag
    }

    return 0;
}

static void LongPressFunc()
{
    if((TouchRegs->ADCDAT0 & (1 << 15)) != 0 && (TouchRegs->ADCDAT1 & (1 << 15)) != 0)       //up interrupt
    {
        input_report_abs(TouchDev, ABS_PRESSURE, 0);
        input_report_key(TouchDev, BTN_TOUCH, 0);
        input_sync(TouchDev);
        WaitInterrupt();
    }
    else
    {
        StartGetPosition();
        StartAD();
    }
}

static int TouchInit(void)
{
    //分配一个input_dev结构体
    TouchDev = input_allocate_device();

    //1. 能产生哪类事件
    set_bit(EV_KEY, TouchDev->evbit);
    set_bit(EV_ABS, TouchDev->evbit);

    //2. 能产生这些事件中的哪些事件
    set_bit(BTN_TOUCH, TouchDev->keybit);
    input_set_abs_params(TouchDev, ABS_X, 0, 0xFFF, 0, 0);
    input_set_abs_params(TouchDev, ABS_Y, 0, 0xFFF, 0, 0);
    input_set_abs_params(TouchDev, ABS_PRESSURE, 0, 1, 0, 0);

    //注册
    input_register_device(TouchDev);

    //硬件相关操作
    //使能clk
    TPClk = clk_get(NULL, "adc");
    clk_enable(TPClk);

    //设置ADC寄存器
    TouchRegs = ioremap(0x7E00B000, 64);
    TouchRegs->ADCCON = (1 << 16) | (1 << 14) | (0xff << 6);
    TouchRegs->ADCDLY = 0xff;

    //注册中断
    int ret = 0;
    ret = request_irq(IRQ_PENDN, TouchIRQ, IRQF_SAMPLE_RANDOM, "TouchHappen", NULL);
    if(ret != 0)
    {
        printk("IRQ IRQ_PENDN register fail\n");
        goto err_irq;
    }
    else
        printk("Register IRQ_PENDN success\n");

    ret = 0;
    request_irq(IRQ_ADC, ADIRQ, IRQF_SAMPLE_RANDOM, "ADC", NULL);
    if(ret != 0)
    {
        printk("IRQ IRQ_PENDN register fail\n");
        goto err_irq;
    }
    else
        printk("Register IRQ_PENDN success\n");

    init_timer(&LongPressTimer);
    LongPressTimer.function = LongPressFunc;
    add_timer(&LongPressTimer);

    TouchRegs->ADCTSC = 0xd3;     //wait interrupt

    return 0;

err_irq:
    clk_disable(TPClk);
    clk_put(TPClk);
    iounmap(TouchRegs);
    input_unregister_device(TouchDev);
    input_free_device(TouchDev);
    return -EINVAL;
}

static void TouchExit(void)
{
    clk_disable(TPClk);
    clk_put(TPClk);
    iounmap(TouchRegs);
    free_irq(IRQ_PENDN, NULL);
    free_irq(IRQ_ADC, NULL);
    input_unregister_device(TouchDev);
    input_free_device(TouchDev);
}

module_init(TouchInit);
module_exit(TouchExit);

MODULE_LICENSE("GPL");
