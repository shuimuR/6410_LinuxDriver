#include <linux/module.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/clk.h>
#include <linux/jiffies.h>
#include <linux/sched.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/partitions.h>

#include <asm/io.h>

#include <plat/regs-nand.h>
#include <plat/nand.h>

static struct nand_chip *s3c_nand;
static struct mtd_info *s3c_mtd;
struct clk *clk;

struct s3c_nand_regs {
    unsigned long nfconf  ;
    unsigned long nfcont  ;
    unsigned long nfcmd   ;
    unsigned long nfaddr  ;
    unsigned long nfdata  ;
    unsigned long nfeccd0 ;
    unsigned long nfeccd1 ;
    unsigned long nfeccd  ;
	unsigned long nfsblk  ;
	unsigned long nfeblk  ;
    unsigned long nfstat  ;
};

static struct s3c_nand_regs *NandRegs;

struct mtd_partition ok6410_nand_part[] = {
	{
		.name		= "Bootloader",
		.offset		= 0,
		.size		= (1 * 0x00100000),
		.mask_flags	= MTD_CAP_NANDFLASH,
	},
	{
		.name		= "Kernel",
		.offset		= (1 * 0x00100000),
		.size		= (5 * 0x00100000) ,
		.mask_flags	= MTD_CAP_NANDFLASH,
	},
	{
		.name		= "File System",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
	}
};

static void MyNandSelect(struct mtd_info *mtd, int chipnr)
{
	if(chipnr == -1)
    {
        //取消选中
        NandRegs->nfcont |= (1 << 1) | (1 << 2);
    }
    else
    {
        //选中
        NandRegs->nfcont &= ~((1 << 1) | (1 << 2));
    }
}

static void MyNandHWControl(struct mtd_info *mtd, int cmd,
                          unsigned int ctrl)
{
	if (ctrl & NAND_CLE)
    {
        //发命令
        NandRegs->nfcmd = cmd;
    }
    else
    {
        //发地址
        NandRegs->nfaddr = cmd;
    }
}

static int MyNandReady(struct mtd_info *mtd)
{
    return (NandRegs->nfstat & (1 << 0));
}

static int __init MyNandInit(void)
{
	NandRegs = ioremap(0x70200000, sizeof(struct s3c_nand_regs));

	//1. 分配nand_chip结构体
	s3c_nand = kzalloc(sizeof(struct nand_chip), GFP_KERNEL);

	//2. 设置
	printk("Set s3c_nand\n");
	s3c_nand->select_chip = MyNandSelect;
    s3c_nand->IO_ADDR_R = &NandRegs->nfdata;;
    s3c_nand->IO_ADDR_W = &NandRegs->nfdata;;
    s3c_nand->cmd_ctrl = MyNandHWControl;
    s3c_nand->dev_ready = MyNandReady;
    s3c_nand->ecc.mode = NAND_ECC_SOFT;

	//硬件相关操作
	printk("Nand clk enable\n");
	clk = clk_get(NULL, "nand");
	clk_enable(clk);
	//HCLK = 100MHz
#define TACLS   5
#define TWRPH0  5
#define TWRPH1  5
    NandRegs->nfconf = (TACLS << 12) | (TWRPH0 << 8) | (TWRPH1 << 4) | (1 << 2);

    //使能nand控制器
    NandRegs->nfcont = (1 << 1) | ( 1 << 0);

	//4. 使用
	s3c_mtd = kzalloc(sizeof(struct mtd_info), GFP_KERNEL);
	s3c_mtd->owner = THIS_MODULE;
	s3c_mtd->priv = s3c_nand;

    nand_scan(s3c_mtd, 1);

	printk("add_mtd_partitions\n");
    //分区信息在change/mach-smdk6410.h
	mtd_device_register(s3c_mtd, ok6410_nand_part, 3);
    return 0;
}

static void __exit MyNandExit(void)
{
	kfree(s3c_mtd);
    clk_disable(clk);
    iounmap(NandRegs);
	mtd_device_unregister(s3c_mtd);
}

module_init(MyNandInit);
module_exit(MyNandExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Slieart");
MODULE_DESCRIPTION("Nand driver");
