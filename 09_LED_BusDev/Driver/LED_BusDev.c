#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/irq.h>

#include <asm/gpio.h>
#include <asm/io.h>

static struct resource LED_Res[] =
{
    [0] = {
        .start = 0x7F008820,
        .end = 0x7F008820 + 16 - 1,
        .flags = IORESOURCE_MEM,
    },
    [1] = {
        .start = 8,
        .end = 8,
        .flags = IORESOURCE_IRQ,
    }
};

static void LED_DevRelease(void)
{

}

static struct platform_device LED_BusDev =
{
    .name = "MyLED",
    .id = 7,
    .num_resources = ARRAY_SIZE(LED_Res),
    .resource = LED_Res,
    .dev = {
        .release = LED_DevRelease,
    },
};

static int LED_BusDevInit(void)
{
    platform_device_register(&LED_BusDev);
    return 0;
}

static void LED_BusDevExit(void)
{
    platform_device_unregister(&LED_BusDev);
}

module_init(LED_BusDevInit);
module_exit(LED_BusDevExit);

MODULE_LICENSE("GPL");
