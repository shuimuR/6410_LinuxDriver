/********************************************
 * 参考文件
 * drivers/block/xd.c
 * drivers/block/z2ram.c
 */

#include <linux/module.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/genhd.h>
#include <linux/hdreg.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/wait.h>
#include <linux/blkdev.h>
#include <linux/mutex.h>
#include <linux/blkpg.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/gfp.h>

#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/dma.h>

static struct gendisk *RamDisk;
static struct request_queue *RamBlockQueue;
static DEFINE_SPINLOCK(RamBlockLock);
static int major;
static unsigned char *RamBlockBuffer;

#define RamBlockSize (1024*1024)

static struct block_device_operations RamBlock_fops =
{
    .owner = THIS_MODULE,
};

static void DoRamBlockRequest(struct request_queue *q)
{
    static int r_cnt = 0;
    static int w_cnt = 0;
    static int cnt = 0;

    struct request *req;

    while((req = blk_fetch_request(q)) != NULL)
    {
        unsigned long offset = blk_rq_pos(req) * 512;

        unsigned long len = blk_rq_cur_sectors(req);

        if(rq_data_dir(req) == READ)
        {
            memcpy(req->buffer, RamBlockBuffer + offset, len);
            printk("read count = %d\n", ++r_cnt);
        }
        else if(rq_data_dir(req) == WRITE)
        {
            memcpy(RamBlockBuffer + offset, req->buffer, len);
            printk("write count = %d\n", ++w_cnt);
        }

        //done
        if (!__blk_end_request_cur(req, 0))
			req = blk_fetch_request(q);
    }

    printk("DoRamBlockRequest %d\n", ++cnt);
}

static int RAMBlockInit(void)
{
    //分配一个gendisk结构体
    RamDisk = alloc_disk(2);    //最多几个分区

    //设置
    //分配一个队列，提供读写能力
    RamBlockQueue = blk_init_queue(DoRamBlockRequest, &RamBlockLock);
    RamDisk->queue = RamBlockQueue;

    //设置其他属性
    major = register_blkdev(0, "RamBlock");
    RamDisk->major = major;
    RamDisk->first_minor = 0;
    sprintf(RamDisk->disk_name, "RamBlock");
    RamDisk->fops = &RamBlock_fops;

    set_capacity(RamDisk, RamBlockSize/512);

    RamBlockBuffer = kzalloc(RamBlockSize, GFP_KERNEL);

    //注册
    add_disk(RamDisk);
    return 0;
}

static void RAMBlockExit(void)
{
    del_gendisk(RamDisk);
    put_disk(RamDisk);
    unregister_blkdev(major, "RamBlock");

    blk_cleanup_queue(RamBlockQueue);
    kfree(RamBlockBuffer);
}

module_init(RAMBlockInit);
module_exit(RAMBlockExit);

MODULE_LICENSE("GPL");
