#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/poll.h>
#include <linux/cdev.h>
#include <linux/device.h>

static int major;

static int Hello1Open(struct inode *inode, struct file *file)
{
    printk("Hello1 open\n");
    return 0;
}

static int Hello2Open(struct inode *inode, struct file *file)
{
    printk("Hello2 open\n");
    return 0;
}

#define HelloCNT 2

static struct file_operations Hello1Ops =
{
    .owner = THIS_MODULE,
    .open = Hello1Open,
};

static struct file_operations Hello2Ops =
{
    .owner = THIS_MODULE,
    .open = Hello2Open,
};

static struct class *HelloClass;

static struct cdev Hello1_Dev;
static struct cdev Hello2_Dev;

static int HelloInit(void)
{
    dev_t devid;

    printk("HelloInit");

    //只关联此设备号为0,1的两个设备
    if(major)
    {
        devid = MKDEV(major, 0);
        register_chrdev_region(devid, HelloCNT, "Hello");
    }
    else
    {
        alloc_chrdev_region(&devid, 0, HelloCNT, "Hello");
        major = MAJOR(devid);
    }

    cdev_init(&Hello1_Dev, &Hello1Ops);
    cdev_add(&Hello1_Dev, devid, HelloCNT);

    //add Hello2
    devid = MKDEV(major, 2);
    register_chrdev_region(devid, 1, "Hello2");     //得到devid
    cdev_init(&Hello2_Dev, &Hello2Ops);     //相当于用Hello2Ops初始化Hello2_Dev
    cdev_add(&Hello2_Dev, devid, 1);        //将Hello2_Dev与devid关联

    HelloClass = class_create(THIS_MODULE, "Hello");
    if(IS_ERR(HelloClass))
        return PTR_ERR(HelloClass);

    device_create(HelloClass, NULL, MKDEV(major, 0), NULL, "%s","Hello0");
    device_create(HelloClass, NULL, MKDEV(major, 1), NULL, "%s","Hello1");
    device_create(HelloClass, NULL, MKDEV(major, 2), NULL, "%s","Hello2");
    device_create(HelloClass, NULL, MKDEV(major, 3), NULL, "%s","Hello3");

    return 0;
}

static void HelloExit(void)
{
    device_destroy(HelloClass, MKDEV(major, 0));
    device_destroy(HelloClass, MKDEV(major, 1));
    device_destroy(HelloClass, MKDEV(major, 2));
    device_destroy(HelloClass, MKDEV(major, 3));
    class_destroy(HelloClass);
    
    cdev_del(&Hello1_Dev);
    unregister_chrdev_region(MKDEV(major, 0), HelloCNT);

    cdev_del(&Hello2_Dev);
    unregister_chrdev_region(MKDEV(major, 2), 1);

    printk("FirstDrv exit\n");
}

module_init(HelloInit);
module_exit(HelloExit);

MODULE_LICENSE("GPL");
