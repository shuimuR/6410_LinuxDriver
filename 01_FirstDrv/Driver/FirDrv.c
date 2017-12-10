#include <linux/kernel.h>
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

#include <asm/io.h>
#include <asm/irq.h>

//LED1-4   GPM0~3
volatile unsigned long *gpmcon;
volatile unsigned long *gpmdat;

int FirstDrvOpen(const char *pathname, int flags)
{
    printk("First drv open\n");

    *gpmcon |= ~((0x0f << (3*4)) | (0x0f << (2*4)) | (0x0f << (1*4)) | (0x0f << (0*4)));
    *gpmcon |= ~((0x01 << (3*4)) | (0x01 << (2*4)) | (0x01 << (1*4)) | (0x01 << (0*4)));
    *gpmdat = 0x0F;

    return 0;
}

int FirstDrvWrite(int fd, const void *buf, size_t count)
{
    printk("First drv write\n");
    int value = 0;
    copy_from_user(&value, buf, count);

    if(value == 1)
    {
        *gpmdat = 0x00;
    }
    else
    {
        *gpmdat = 0x0F;
    }
    return 0;
}


static struct file_operations FirDrvStruct =
{
    .owner = THIS_MODULE,
    .open = FirstDrvOpen,
    .write = FirstDrvWrite,
};

int major;
static struct class *FirDrvClass;
static struct class_device *FirDrvClassDev;

static int FirDrvInit()
{
    printk("FirstDrv Init\n");
    //major = register_chrdev(major, "FirDev", &FirDrvStruct);
    major = register_chrdev(0, "FirDev", &FirDrvStruct);
#if 1
    //Auto create the node
    FirDrvClass = class_create(THIS_MODULE, "FirDrv");
    if(IS_ERR(FirDrvClass))
    {
        return PTR_ERR(FirDrvClass);
    }

    FirDrvClassDev = device_create(FirDrvClass, NULL, MKDEV(major, 0), NULL, "%s","Hello");
    /*if(unlikely(FirDrvClassDev))
    {
        printk("Error to create device\n");
        class_destroy(FirDrvClass);
        return PTR_ERR(FirDrvClassDev);
    }*/
#endif

    gpmcon = (volatile unsigned long *)ioremap(0x7F008820, 16);
    gpmdat = gpmcon + 1;

    return 0;
}

static void FirDrvExit()
{
    unregister_chrdev(major, "FirDev");
    device_destroy(FirDrvClassDev, MKDEV(major, 0));
    class_destroy(FirDrvClass);
    printk("FirstDrv exit\n");
}

module_init(FirDrvInit);
module_exit(FirDrvExit);

MODULE_LICENSE("GPL");