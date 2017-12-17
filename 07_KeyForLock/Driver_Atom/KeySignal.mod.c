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
	{ 0x6d4a8ee9, "kill_fasync" },
	{ 0xb9e52429, "__wake_up" },
	{ 0x80ab0c30, "add_timer" },
	{ 0x3028e855, "init_timer_key" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x7d11c268, "jiffies" },
	{ 0x98082893, "__copy_to_user" },
	{ 0x8893fa5d, "finish_wait" },
	{ 0x75a17bed, "prepare_to_wait" },
	{ 0x1000e51, "schedule" },
	{ 0x1298ac43, "mod_timer" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0x779636b1, "device_create" },
	{ 0x4c38cbec, "__class_create" },
	{ 0x78713c2f, "__register_chrdev" },
	{ 0x7807f663, "fasync_helper" },
	{ 0x27e1a049, "printk" },
	{ 0xd1671060, "del_timer" },
	{ 0x45a55ec8, "__iounmap" },
	{ 0x8b6dfcfd, "class_destroy" },
	{ 0x1b73a865, "device_destroy" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "1AB64E2BB9C31D8933065B1");
