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
#include <linux/dma-mapping.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/clk.h>

static char *src;
static u32 src_phy;

static char *dst;
static u32 dst_phy;

//ioctrl中使用的信号
static DECLARE_WAIT_QUEUE_HEAD(DMA_waitq);
static volatile int ev_dma = 0;

#define SDMA0_BASE1 (0x7DB00000)
#define SDMA0_BASE2 (0x7DB00000 + 0x100)
struct SDMA_Regs_Part1
{
    unsigned long DMACIntStatus;
    unsigned long DMACIntTCStatus;
    unsigned long DMACIntTCClear;
    unsigned long DMACIntErrorStatus;
    unsigned long DMACIntErrClr;
    unsigned long DMACRawIntTCStatus;
    unsigned long DMACRawIntErrorStatus;
    unsigned long DMACEnbldChns;
    unsigned long DMACSoftBReq;
    unsigned long DMACSoftSReq;
    unsigned long Reserved1;
    unsigned long Reserved2;
    unsigned long DMACConfiguration;
    unsigned long DMACSync;
};

struct SDMA_Regs_Part2
{
    unsigned long DMACC0SrcAddr;
    unsigned long DMACC0DestAddr;
    unsigned long DMACC0LLI;
    unsigned long DMACC0Control0;
    unsigned long DMACC0Control1;
    unsigned long DMACC0Configuration;
    unsigned long DMACC0ConfigurationExp;
};

static volatile struct SDMA_Regs_Part1 *SDMA_Regs1;
static volatile struct SDMA_Regs_Part2 *SDMA_Regs2;

#define SDMA_SEL_BASE 0x7E00F110
static volatile unsigned long *SDMA_SEL = NULL;

#define BUF_SIZE (512 * 1024)

#define MEM_CPY_NO_DMA  0
#define MEM_CPY_DMA     1

static int DMA_IOCtl(struct file *file, unsigned int cmd, unsigned long arg)
{
    memset(src, 0xAA, BUF_SIZE);
    memset(dst, 0x55, BUF_SIZE);

    switch(cmd)
    {
        case MEM_CPY_NO_DMA:
        {
            printk("Use no DMA copy\n");
            int i;
            for(i = 0; i < BUF_SIZE; i++)
            {
                dst[i] = src[i];
            }

            if(memcmp(src, dst, BUF_SIZE) == 0)
                printk("NO DMA src = dst\n");
            else
                printk("NO DMA src != dst\n");
            break;
        }
        case MEM_CPY_DMA:
        {
            printk("Use DMA copy\n");

            struct clk	*clk;
            clk = clk_get(NULL, "sdma0");
        	if (IS_ERR(clk)) {
        		printk(KERN_ERR "%s: failed to get clock sdma0\n", __func__);
        		return -1;
        	}
        	clk_enable(clk);

            SDMA_Regs1 = ioremap(SDMA0_BASE1, sizeof(struct SDMA_Regs_Part1));
            SDMA_Regs2 = ioremap(SDMA0_BASE2, sizeof(struct SDMA_Regs_Part2));
            SDMA_SEL = ioremap(SDMA_SEL_BASE, 4);

            *SDMA_SEL = 0;              //use SDMA0

            //enable SDMA0
            SDMA_Regs1->DMACConfiguration = 1;

            //Addr set
            SDMA_Regs2->DMACC0SrcAddr = src_phy;
            SDMA_Regs2->DMACC0DestAddr = dst_phy;

            //enable software Start
            SDMA_Regs1->DMACSoftSReq = 0x01;

            //Config
            SDMA_Regs2->DMACC0Control0 = (1 << 26) | (1 << 27) | (1 << 31);
            SDMA_Regs2->DMACC0Control1 = BUF_SIZE;

            //enable interrupt and start SDMA
            SDMA_Regs2->DMACC0Configuration =  (1 << 15) | (1 << 14) | 1;

            //开始休眠  在中断中唤醒
            printk("start to wait finish\n");
            wait_event_interruptible(DMA_waitq, ev_dma);
            printk("After wake up, the ev_dma = %d\n", ev_dma);
            ev_dma = 0;

            if(memcmp(src, dst, BUF_SIZE) == 0)
                printk("use DMA src = dst\n");
            else
                printk("use DMA src != dst\n");
            break;
        }
    }
    return 0;
}

static struct file_operations DMA_Ops =
{
    .owner = THIS_MODULE,
    .unlocked_ioctl = DMA_IOCtl,
};

static struct class *DMAClass;
static struct cdev DMA_Dev;
int major;
#define DMA_DevCNT 1

static irqreturn_t DMA_Irq(int irq, void *devid)
{
    printk("SDMA0 interrupt\n");
    SDMA_Regs1->DMACIntTCClear |= 0x01;
    ev_dma = 1;
    wake_up_interruptible(&DMA_waitq);
    return IRQ_HANDLED;
}

static int DMA_Init(void)
{
    //分配src dst对应的缓冲区，不能用malloc，因为如果用malloc分配
    //可能得到物理地址不连续的存储空间
    src = dma_alloc_writecombine(NULL, BUF_SIZE, &src_phy, GFP_KERNEL);
    if(src == NULL)
    {
        printk("Can't alloc src memory\n");
        return -ENOMEM;
    }
    else
        printk("The source phys addr is 0x%08x\n", src_phy);

    dst = dma_alloc_writecombine(NULL, BUF_SIZE, &dst_phy, GFP_KERNEL);
    if(dst == NULL)
    {
        printk("Can't alloc dst memory\n");
        return -ENOMEM;
    }
    else
        printk("The dest phys addr is 0x%08x\n", dst_phy);

    //注册字符设备
    dev_t devid;
    alloc_chrdev_region(&devid, 0, DMA_DevCNT, "DMA_Test");
    major = MAJOR(devid);
    cdev_init(&DMA_Dev, &DMA_Ops);
    cdev_add(&DMA_Dev, devid, DMA_DevCNT);

    DMAClass = class_create(THIS_MODULE, "DMA_Test");
    if(IS_ERR(DMAClass))
        return PTR_ERR(DMAClass);
    device_create(DMAClass, NULL, MKDEV(major, 0), NULL, "%s","DMA_Test");

    //注册DMA中断
    if(request_irq(IRQ_SDMA0, DMA_Irq, 0, "SDMA_IRQ", NULL))
    {
        printk("Can't register irq for SDMA0\n");

        device_destroy(DMAClass, MKDEV(major, 0));
        class_destroy(DMAClass);

        cdev_del(&DMA_Dev);
        unregister_chrdev_region(MKDEV(major, 0), DMA_DevCNT);

        dma_free_writecombine(NULL, BUF_SIZE, src, src_phy);
        dma_free_writecombine(NULL, BUF_SIZE, dst, dst_phy);
    }
    return 0;
}

static void DMA_Exit(void)
{
    device_destroy(DMAClass, MKDEV(major, 0));
    class_destroy(DMAClass);

    cdev_del(&DMA_Dev);
    unregister_chrdev_region(MKDEV(major, 0), DMA_DevCNT);

    free_irq(IRQ_SDMA0, NULL);

    iounmap(SDMA_SEL);
    iounmap(SDMA_Regs1);
    iounmap(SDMA_Regs2);
}

module_init(DMA_Init);
module_exit(DMA_Exit);

MODULE_LICENSE("GPL");
