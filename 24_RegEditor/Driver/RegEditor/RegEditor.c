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
#include <linux/irq.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>

typedef enum {CMD_R8, CMD_R16, CMD_R32, CMD_W8, CMD_W16, CMD_W32}CMD_Type;

static int RegEditIOCtrl(struct file *file, unsigned int cmd, unsigned long arg)
{
    CMD_Type Command = cmd;
    unsigned int val = 0;
    unsigned int addr = 0;
    unsigned buf[2];

    volatile unsigned char *p8 = NULL;
    volatile unsigned short *p16 = NULL;
    volatile unsigned int *p32 = NULL;

    copy_from_user(buf, (const void __user *)arg, 8);
    addr = buf[0];
    val = buf[1];

    p8 = (volatile unsigned char *)ioremap(addr, 4);
    p16 = (volatile unsigned short *)p8;
    p32 = (volatile unsigned int *)p8;

    switch(Command)
    {
        case CMD_R8:
            val = *p8;
            copy_to_user((void __user *)(arg + 4), &val, 4);
            break;
        case CMD_R16:
            val = *p16;
            copy_to_user((void __user *)(arg + 4), &val, 4);
            break;
        case CMD_R32:
            val = *p16;
            copy_to_user((void __user *)(arg + 4), &val, 4);
            break;
        case CMD_W8:
            *p8 = val;
            break;
        case CMD_W16:
            *p16 = val;
            break;
        case CMD_W32:
            *p32 = val;
            break;
    }

    iounmap(p8);
    return 0;
}

static struct file_operations RegEditOps =
{
    .owner = THIS_MODULE,
    .unlocked_ioctl = RegEditIOCtrl,
};

static int major;
#define DevCount 1
static struct class *RegEditorCls;
static struct cdev RegEditorDev;

static int RegEditorInit(void)
{
    dev_t devid;
    alloc_chrdev_region(&devid, 0, DevCount, "RegEditor");
    major = MAJOR(devid);
    cdev_init(&RegEditorDev, &RegEditOps);
    cdev_add(&RegEditorDev, devid, DevCount);
    RegEditorCls = class_create(THIS_MODULE, "RegEditor");
    device_create(RegEditorCls, NULL, MKDEV(major, 0), NULL, "%s","RegEditor");
    return 0;
}

static void RegEditorExit(void)
{
    device_destroy(RegEditorCls, MKDEV(major, 0));
    class_destroy(RegEditorCls);
    cdev_del(&RegEditorDev);
    unregister_chrdev_region(MKDEV(major, 0), DevCount);
}

module_init(RegEditorInit);
module_exit(RegEditorExit);

MODULE_LICENSE("GPL");
