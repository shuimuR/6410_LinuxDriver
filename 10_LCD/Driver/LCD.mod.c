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
	{ 0x2f168e67, "cfb_imageblit" },
	{ 0xb92af82d, "cfb_copyarea" },
	{ 0x5746d7e5, "cfb_fillrect" },
	{ 0x75c1ab20, "register_framebuffer" },
	{ 0x9fcdf9e8, "dma_alloc_writecombine" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0xf770a3fb, "framebuffer_alloc" },
	{ 0x874e8664, "framebuffer_release" },
	{ 0x45a55ec8, "__iounmap" },
	{ 0x85342a82, "dma_free_coherent" },
	{ 0xfc174f5, "unregister_framebuffer" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "568D794D79C8D49C26E45F2");
