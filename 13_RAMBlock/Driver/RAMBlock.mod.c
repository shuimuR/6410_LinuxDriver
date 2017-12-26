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
	{ 0xb698c2b0, "__blk_end_request_cur" },
	{ 0x27e1a049, "printk" },
	{ 0x9d669763, "memcpy" },
	{ 0xf16f7e4f, "blk_fetch_request" },
	{ 0xd432fc42, "add_disk" },
	{ 0x86a4889a, "kmalloc_order_trace" },
	{ 0x71a50dbc, "register_blkdev" },
	{ 0x8794de6c, "blk_init_queue" },
	{ 0xffb64aac, "alloc_disk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x37a0cba, "kfree" },
	{ 0xb8b5d3b9, "blk_cleanup_queue" },
	{ 0xb5a459dc, "unregister_blkdev" },
	{ 0x6c4133e0, "put_disk" },
	{ 0x8e4594c6, "del_gendisk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "0A8F94D1612C7B06428AF19");
