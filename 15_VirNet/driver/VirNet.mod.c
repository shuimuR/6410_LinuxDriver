#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd0a8ddc4, "module_layout" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x5d0abba3, "__netif_schedule" },
	{ 0xb2c2fd2f, "consume_skb" },
	{ 0xf3baee00, "netif_rx" },
	{ 0x619c6e67, "eth_type_trans" },
	{ 0x4554b64, "skb_put" },
	{ 0x75e857c7, "dev_alloc_skb" },
	{ 0x9d669763, "memcpy" },
	{ 0x7cb6594e, "ether_setup" },
	{ 0x9e4c3efd, "register_netdev" },
	{ 0xbe908e6a, "alloc_netdev_mqs" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xc6afd00c, "free_netdev" },
	{ 0x377d4af3, "unregister_netdev" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "522FF072D700166484C0C71");
