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

//Key1-6   GPN0~N5
volatile unsigned long *gpncon;
volatile unsigned long *gpndat;
volatile unsigned long *gpnpud;

int ScanKeyOpen(const char *pathname, int flags)
{
    printk("Scan Key open\n");

    *gpncon &= ~((0x03 << (5*2)) | (0x03 << (4*2)) | (0x03 << (3*2)) | (0x03 << (2*2)) | (0x03 << (1*2)) | (0x03 << (0*2)));
    *gpnpud |= ((0x02 << (5*2)) | (0x02 << (4*2)) | (0x02 << (3*2)) | (0x02 << (2*2)) | (0x02 << (1*2)) | (0x03 << (0*2)));

    return 0;
}

int ScanKeyRead(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
    //printk("Scan key read\n");
    char value[6] = {0};
    int regval = 0;
    if(size != 6)
    {
        printk("There are 6 keys, so you must read 6 datas\n");
        return -1;
    }

    regval = *gpndat;
    //printk("gpndat = %x\n", regval);
    value[0] = (regval & (1 << 0) ? 0 : 1);
    value[1] = (regval & (1 << 1) ? 0 : 1);
    value[2] = (regval & (1 << 2) ? 0 : 1);
    value[3] = (regval & (1 << 3) ? 0 : 1);
    value[4] = (regval & (1 << 4) ? 0 : 1);
    value[5] = (regval & (1 << 5) ? 0 : 1);
    copy_to_user(buf, value, sizeof(value));

    return 0;
}


static struct file_operations ScanKeyFiles =
{
    .owner = THIS_MODULE,
    .open = ScanKeyOpen,
    .read = ScanKeyRead,
};

int major;
static struct class *ScanKeyClass;
static struct class_device *ScanKeyClassDev;

static int ScanKeyInit()
{
    printk("Scan key Init\n");
    major = register_chrdev(0, "ScanKey", &ScanKeyFiles);
#if 1
    //Auto create the node
    ScanKeyClass = class_create(THIS_MODULE, "ScanKey");
    if(IS_ERR(ScanKeyClass))
    {
        return PTR_ERR(ScanKeyClass);
    }

    ScanKeyClassDev = device_create(ScanKeyClass, NULL, MKDEV(major, 0), NULL, "%s","ScanKey1");
    /*if(unlikely(FirDrvClassDev))
    {
        printk("Error to create device\n");
        class_destroy(FirDrvClass);
        return PTR_ERR(FirDrvClassDev);
    }*/
#endif

    gpncon = (volatile unsigned long *)ioremap(0x7F008830, 16);
    gpndat = gpncon + 1;
    gpnpud = gpncon + 2;

    return 0;
}

static void ScanKeyExit()
{
    device_destroy(ScanKeyClass, MKDEV(major, 0));
    class_destroy(ScanKeyClass);
    unregister_chrdev(major, "ScanKey");
    printk("Scan Key exit\n");
}

module_init(ScanKeyInit);
module_exit(ScanKeyExit);

MODULE_LICENSE("GPL");
