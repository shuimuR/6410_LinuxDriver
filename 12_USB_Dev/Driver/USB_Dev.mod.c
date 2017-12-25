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
	{ 0x8cba40e8, "usb_register_driver" },
	{ 0x6c17353, "input_event" },
	{ 0x7184aa1b, "usb_submit_urb" },
	{ 0x38814571, "usb_alloc_urb" },
	{ 0xe3349780, "usb_alloc_coherent" },
	{ 0x34d335c7, "input_register_device" },
	{ 0xf48bc2e3, "input_allocate_device" },
	{ 0x6e8d2b4, "input_free_device" },
	{ 0xc392e6d4, "input_unregister_device" },
	{ 0x9b193202, "usb_free_coherent" },
	{ 0x35d12272, "usb_free_urb" },
	{ 0x5708eb67, "usb_kill_urb" },
	{ 0x27e1a049, "printk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xfc8641ac, "usb_deregister" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "2DF3265AAD8AF47B802E5CD");
