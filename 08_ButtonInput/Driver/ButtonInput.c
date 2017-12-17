#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/unistd.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/input.h>

#include <asm/io.h>
#include <asm/irq.h>


#include <asm/types.h>	     // for variable types

//Key1-6   GPN0~N5
volatile unsigned long *gpncon;
volatile unsigned long *gpndat;
volatile unsigned long *gpnpud;

unsigned char KeyVal = 0;

#if 0
static irqreturn_t ButtonsIRQ(int irq, void *dev_id)
{
    printk("irq = %d\n", irq);

    unsigned long RegVal = *gpndat;

    if(irq == IRQ_EINT0_3)
    {
        if(RegVal == 0x7e)
            KeyVal = 0;
        else if(RegVal == 0x7d)
            KeyVal = 1;
        else if(RegVal == 0x7b)
            KeyVal = 2;
        else if(RegVal == 0x77)
            KeyVal = 3;
        else if(RegVal == 0x6F)
            KeyVal = 4;
    }
    else
    {
        if(RegVal == 0x5F)
            KeyVal = 5;
    }

    //wake up to read
    ReadFlag = 1;
    wake_up_interruptible(&Buttons_WaitQ);

    return IRQ_HANDLED;
}
#endif

static struct timer_list SimulateButtonTimer;

static struct input_dev *ButtonDev;

typedef enum{Stage_L, Stage_S, Stage_ENTER}SendKeyStep;

SendKeyStep SendKeyStepNow = Stage_L;

static void SimulateTimerFunc(unsigned long time)
{
    //printk("SimulateTimerFunc runs, SendKeyStepNow = %d\n", SendKeyStepNow);
    mod_timer(&SimulateButtonTimer, jiffies + HZ*3);		//jiffies every 3s system timeout
    #if 1
    switch(SendKeyStepNow)
    {
        case Stage_L:
            input_event(ButtonDev, EV_KEY, KEY_L, 1);
            input_sync(ButtonDev);
            input_event(ButtonDev, EV_KEY, KEY_L, 0);
            input_sync(ButtonDev);
            SendKeyStepNow = Stage_S;
            break;
        case Stage_S:
            input_event(ButtonDev, EV_KEY, KEY_S, 1);
            input_sync(ButtonDev);
            input_event(ButtonDev, EV_KEY, KEY_S, 0);
            input_sync(ButtonDev);
            SendKeyStepNow = Stage_ENTER;
            break;
        case Stage_ENTER:
            input_event(ButtonDev, EV_KEY, KEY_ENTER, 1);
            input_sync(ButtonDev);
            input_event(ButtonDev, EV_KEY, KEY_ENTER, 0);
            input_sync(ButtonDev);
            SendKeyStepNow = Stage_L;
            break;
        default:
            SendKeyStepNow = Stage_L;
            break;
    }
    #endif
}

int major;
static struct class *KeyIntrClass;
static struct class_device *KeyIntrClassDev;

static int KeyIntrInit()
{
    init_timer(&SimulateButtonTimer);
    SimulateButtonTimer.function = SimulateTimerFunc;
    add_timer(&SimulateButtonTimer);

    ButtonDev = input_allocate_device();

    set_bit(EV_KEY, ButtonDev->evbit);
    set_bit(EV_REP, ButtonDev->evbit);

    set_bit(KEY_L, ButtonDev->keybit);
    set_bit(KEY_S, ButtonDev->keybit);
    set_bit(KEY_ENTER, ButtonDev->keybit);

    int ret = 0;
    ret = input_register_device(ButtonDev);

    mod_timer(&SimulateButtonTimer, jiffies + HZ*3);		//jiffies every 3s system timeout
    #if 0
    int ret = 0;
    unsigned char *Point = "Hello world";

    ret = request_irq(IRQ_EINT0_3, ButtonsIRQ, IRQ_TYPE_EDGE_RISING | IRQ_NOREQUEST, "ButtonsG1", Point);
    if(ret != 0)
        printk("register IRQ_EINT0_3 fail, ret = %d\n", ret);

    ret = 0;
    ret = request_irq(IRQ_EINT4_11, ButtonsIRQ, IRQ_TYPE_EDGE_RISING | IRQ_NOREQUEST, "ButtonsG2", Point);
    if(ret != 0)
        printk("register IRQ_EINT4_11 fail, ret = %d\n", ret);

    if (ret == 0)
        IRQ_HasRegister = 1;
#endif

    return 0;
}

static void KeyIntrExit()
{
    input_unregister_device(ButtonDev);
	input_free_device(ButtonDev);
    del_timer(&SimulateButtonTimer);
#if 0
    if(IRQ_HasRegister == 1)
    {
        free_irq(IRQ_EINT0_3, NULL);
        free_irq(IRQ_EINT4_11, NULL);
    }
#endif

    printk("Key Intr exit\n");
}

module_init(KeyIntrInit);
module_exit(KeyIntrExit);

MODULE_LICENSE("GPL");
