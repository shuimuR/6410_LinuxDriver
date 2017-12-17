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
	{ 0x6c17353, "input_event" },
	{ 0x7d11c268, "jiffies" },
	{ 0x1298ac43, "mod_timer" },
	{ 0x34d335c7, "input_register_device" },
	{ 0xf48bc2e3, "input_allocate_device" },
	{ 0x80ab0c30, "add_timer" },
	{ 0x3028e855, "init_timer_key" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x27e1a049, "printk" },
	{ 0xd1671060, "del_timer" },
	{ 0x6e8d2b4, "input_free_device" },
	{ 0xc392e6d4, "input_unregister_device" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "9CA078D95906E1D4AACB769");
