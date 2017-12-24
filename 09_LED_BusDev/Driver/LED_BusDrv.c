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
#include <linux/uaccess.h>

#include <asm/gpio.h>
#include <asm/io.h>

volatile unsigned long *gpmcon;
volatile unsigned long *gpmdat;

static int LED_BusDrvOpen(struct inode *inode, struct file *file)
{
    printk("call LED_BusDrvOpen\n");
    *gpmcon |= ~((0x0f << (3*4)) | (0x0f << (2*4)) | (0x0f << (1*4)) | (0x0f << (0*4)));
    *gpmcon |= ~((0x01 << (3*4)) | (0x01 << (2*4)) | (0x01 << (1*4)) | (0x01 << (0*4)));
    *gpmdat = 0x0F;
    return 0;
}

static ssize_t LED_BusDrvWrite(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
    int i;
    char val[4] = {0};

    if(count != 4)
    {
        printk("The value count should be 4\n");
        return -EINVAL;
    }
    copy_from_user(val, buf, count);

    if(val[0] == 0)
        printk("The first num is 0\n");
    else
        printk("The first num is 1\n");

    for(i = 0; i < 4; i++)
    {
        if(val[i] == 0)
            *gpmdat &= ~(1 << i);
        else
            *gpmdat |= (1 << i);
    }
    return 0;
}

int major;
static struct class *LEDBusClass;
static struct class_device *LEDBusClassDev;

static struct file_operations LED_BusDrvFs =
{
    .owner = THIS_MODULE,
    .write = LED_BusDrvWrite,
    .open = LED_BusDrvOpen,
};

static int LED_BusDrvProbe(struct platform_device *dev)
{
    struct resource *res;

    //根据dev传入的resource获取硬件参数
    res = platform_get_resource(dev, IORESOURCE_MEM, 0);
    gpmcon = ioremap(res->start, res->end - res->start + 1);
    gpmdat = gpmcon + 1;

    printk("call LED_BusDrvProbe\n");

    //注册节点
    major = register_chrdev(0, "LEDBus", &LED_BusDrvFs);
    LEDBusClass = class_create(THIS_MODULE, "LEDBus");
    if(IS_ERR(LEDBusClass))
    {
        return PTR_ERR(LEDBusClass);
    }

    LEDBusClassDev = device_create(LEDBusClass, NULL, MKDEV(major, 0), NULL, "%s", "LEDBus");

    return 0;
}

static void LED_BusRemove(void)
{
    unregister_chrdev(major, "LEDBus");
    device_destroy(LEDBusClass, MKDEV(major, 0));
    class_destroy(LEDBusClass);
    iounmap(gpmcon);
}

static struct platform_driver LED_BusDrv =
{
    .probe = LED_BusDrvProbe,
    .remove = LED_BusRemove,
    .driver = {
        .name = "MyLED",
    },
};

static int LED_BusDrvInit(void)
{
    platform_driver_register(&LED_BusDrv);
    return 0;
}

static void LED_BusDrvExit(void)
{
    platform_driver_unregister(&LED_BusDrv);
}

module_init(LED_BusDrvInit);
module_exit(LED_BusDrvExit);

MODULE_LICENSE("GPL");
