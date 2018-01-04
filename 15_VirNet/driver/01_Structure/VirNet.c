/***************************************
参考：drivers/net/cs89x0.c
 **************************************/

#include <linux/module.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/skbuff.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/bitops.h>
#include <linux/delay.h>

#include <asm/system.h>
#include <asm/io.h>
#include <asm/irq.h>

static struct net_device *VNetDev;

static int VNetSendPacket(struct sk_buff *skb, struct net_device *dev)
{
    static int cnt = 0;
    printk("virt_net_sendpacket cnt = %d\n", ++cnt);
    return 0;
}

static const struct net_device_ops VNet_ops = {
	.ndo_start_xmit 	= VNetSendPacket,
};

static int VNetInit(void)
{
    printk("VNetInit\n");
    //1. 分配一个net_device结构体
    VNetDev = alloc_netdev(0, "vnet%d", ether_setup);

    //2. 设置
    VNetDev->netdev_ops = &VNet_ops;
    //MAC addr
    #if 0
    VNetDev->dev_addr[0] = 0x77;
    VNetDev->dev_addr[1] = 0x77;
    VNetDev->dev_addr[2] = 0x77;
    VNetDev->dev_addr[3] = 0x77;
    VNetDev->dev_addr[4] = 0x77;
    VNetDev->dev_addr[5] = 0x77;
    #endif
    //3. 注册
    register_netdev(VNetDev);

    return 0;
}

static void VNetExit(void)
{
    printk("VNetExit\n");
    unregister_netdev(VNetDev);
    free_netdev(VNetDev);
}

module_init(VNetInit);
module_exit(VNetExit);

MODULE_LICENSE("GPL");
