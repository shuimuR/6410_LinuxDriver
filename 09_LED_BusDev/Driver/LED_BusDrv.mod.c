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
	{ 0x5420d3dd, "platform_driver_register" },
	{ 0x779636b1, "device_create" },
	{ 0x4c38cbec, "__class_create" },
	{ 0x78713c2f, "__register_chrdev" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0xf108648c, "platform_get_resource" },
	{ 0x17a142df, "__copy_from_user" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x27e1a049, "printk" },
	{ 0x45a55ec8, "__iounmap" },
	{ 0x8b6dfcfd, "class_destroy" },
	{ 0x1b73a865, "device_destroy" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x1f3cc41e, "platform_driver_unregister" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "10D141757B3805CB1B1A514");
