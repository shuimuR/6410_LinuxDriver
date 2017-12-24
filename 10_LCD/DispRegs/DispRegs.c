#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/div64.h>

#include <asm/mach/map.h>

/**********************************************
display the vaules about LCD config
**********************************************/

static volatile unsigned long *LCD_RegBase = NULL;
static volatile unsigned long *HCLK_GATE = NULL;

#define LCD_RegStartAddr 0x77100000
#define LCD_RegEndAddr  0x77100344

static int DisplyRegsInit(void)
{
    LCD_RegBase = ioremap(LCD_RegStartAddr, LCD_RegEndAddr - LCD_RegStartAddr);
    HCLK_GATE = ioremap(0x7E00F030, 16);

    unsigned long Value = 0;
    int i;
    for(i = 0; i < LCD_RegEndAddr - LCD_RegStartAddr; i+=4)
    {
        Value = *(LCD_RegBase + i);
        printk("addr: 0x%lx         Value = 0x%08x\n", LCD_RegStartAddr + i, Value);
    }

    Value = *(HCLK_GATE);
    printk("addr: 0x%lx         Value = 0x%08x\n", 0x7E00F030, Value);
    return 0;
}

static void DisplayRegsExit(void)
{
    iounmap(LCD_RegBase);
    iounmap(HCLK_GATE);
}

module_init(DisplyRegsInit);
module_exit(DisplayRegsExit);

MODULE_LICENSE("GPL");
