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
#include <linux/wait.h>
#include <linux/poll.h>

#include <asm/io.h>
#include <asm/irq.h>


#include <asm/types.h>	     // for variable types

//Key1-6   GPN0~N5
volatile unsigned long *gpncon;
volatile unsigned long *gpndat;
volatile unsigned long *gpnpud;

static volatile unsigned int ReadFlag = 0;
static DECLARE_WAIT_QUEUE_HEAD(Buttons_WaitQ);

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

//驱动传递给app的信号
static struct fasync_struct KeySig;


int KeyIntrOpen(const char *pathname, int flags)
{
    printk("Key Intr open\n");

    return 0;
}

int KeyIntrRead(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
    printk("Key intr read\n");

    if(size != 1)
    {
        printk("You just need to read 1 data\n");
        return -1;
    }

    mod_timer(&SimulateButtonTimer, jiffies + HZ*3);            //every 3s

    //sleep
    wait_event_interruptible(Buttons_WaitQ, ReadFlag);
    printk("There's key event\n");
    copy_to_user(buf, &KeyVal, 1);
    ReadFlag = 0;

    return 0;
}

#if 0
static unsigned int KeyIntrPoll(struct file *file, poll_table *wait)
{
    unsigned int mask = 0;
    poll_wait(file, &Buttons_WaitQ, wait);

    if(ReadFlag)
    {
        mask |= POLLIN | POLLRDNORM;
    }
    return mask;
}
#endif

static int ButtonSync(int fd, struct file *filp, int on)
{
    printk("Driver: Run the ButtonSync\n");
    return fasync_helper(fd, filp, on, &KeySig);
}

static struct file_operations KeyIntrFiles =
{
    .owner = THIS_MODULE,
    .open = KeyIntrOpen,
    .read = KeyIntrRead,
    //.poll = KeyIntrPoll,
    .fasync = ButtonSync,
};

int major;
static struct class *KeyIntrClass;
static struct class_device *KeyIntrClassDev;

unsigned char IRQ_HasRegister = 0;

static void SimulateTimerFunc(unsigned long time)
{
    //wake up to read
    static cnt = 0;
    printk("Timer wake up to read, cnt = %d\n", ++cnt);
    KeyVal = 0x03;
    ReadFlag = 1;
    wake_up_interruptible(&Buttons_WaitQ);

    kill_fasync(&KeySig, SIGIO, POLL_IN);      //send sig
}

static int KeyIntrInit()
{
    printk("Key intr Init\n");
    major = register_chrdev(0, "KeyIntr", &KeyIntrFiles);
    //Auto create the node
    KeyIntrClass = class_create(THIS_MODULE, "KeyIntr");
    if(IS_ERR(KeyIntrClass))
    {
        return PTR_ERR(KeyIntrClass);
    }

    KeyIntrClassDev = device_create(KeyIntrClass, NULL, MKDEV(major, 0), NULL, "%s","KeyIntr");

    gpncon = (volatile unsigned long *)ioremap(0x7F008830, 16);
    gpndat = gpncon + 1;
    gpnpud = gpncon + 2;

    //用timer模拟外部中断
    init_timer(&SimulateButtonTimer);
    SimulateButtonTimer.function = SimulateTimerFunc;
    add_timer(&SimulateButtonTimer);


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
    unregister_chrdev(major, "KeyIntr");
    device_destroy(KeyIntrClass, MKDEV(major, 0));
    class_destroy(KeyIntrClass);
    iounmap(gpncon);
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
