//RGB 888

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/div64.h>

#include <asm/mach/map.h>

//as build, we need the wrong pallte
static u32 pseudo_palette[16];
/* from pxafb.c */
static inline unsigned int chan_to_field(unsigned int chan, struct fb_bitfield *bf)
{
    chan &= 0xffffff;
    chan >>= 24 - bf->length;
    return chan << bf->offset;
}

static int s3c_lcdfb_setcolreg(unsigned int regno, unsigned int red,
                               unsigned int green, unsigned int blue,
                               unsigned int transp, struct fb_info *info)
{
    unsigned int val;

    if (regno > 24)
        return 1;

    /* 用red,green,blue三原色构造出val */
    val  = chan_to_field(red,	&info->var.red);
    val |= chan_to_field(green, &info->var.green);
    val |= chan_to_field(blue,	&info->var.blue);

    //((u32 *)(info->pseudo_palette))[regno] = val;
    pseudo_palette[regno] = val;
    return 0;
}

static struct fb_ops MyLCDOps =
{
    .owner = THIS_MODULE,
    .fb_setcolreg = s3c_lcdfb_setcolreg,
    .fb_fillrect = cfb_fillrect,
    .fb_copyarea = cfb_copyarea,
    .fb_imageblit = cfb_imageblit,
};
static struct fb_info *s3c_lcd;

enum LCD_SFR
{
	//Video Control
	rVIDCON0		= 0x000,
	rVIDCON1		= 0x004,
	rVIDCON2		= 0x008,
	//Video Time Control
	rVIDTCON0       = 0x010,
	rVIDTCON1       = 0x014,
	rVIDTCON2       = 0x018,
	rVIDTCON3       = 0x01c,
	//Window Control
	rWINCON0	    = 0x020,
	rWINCON1        = 0x024,
	rWINCON2	    = 0x028,
	rWINCON3	    = 0x02C,
	rWINCON4	    = 0x030,
	//Video Window Position Control
	rVIDOSD0A       = 0x040,
	rVIDOSD0B       = 0x044,
	rVIDOSD0C       = 0x048,
	rVIDOSD1A       = 0x050,
	rVIDOSD1B       = 0x054,
	rVIDOSD1C       = 0x058,
	rVIDOSD1D       = 0x05C,
	rVIDOSD2A       = 0x060,
	rVIDOSD2B       = 0x064,
	rVIDOSD2C       = 0x068,
	rVIDOSD2D       = 0x06c,
	rVIDOSD3A       = 0x070,
	rVIDOSD3B       = 0x074,
	rVIDOSD3C       = 0x078,
	rVIDOSD4A       = 0x080,
	rVIDOSD4B       = 0x084,
	rVIDOSD4C       = 0x088,
	//Window Buffer Start Address
	rVIDW00ADD0B0   = 0x0A0,
	rVIDW00ADD0B1   = 0x0A4,
	rVIDW01ADD0B0   = 0x0A8,
	rVIDW01ADD0B1   = 0x0AC,
	rVIDW02ADD0     = 0x0B0,
	rVIDW03ADD0     = 0x0B8,
	rVIDW04ADD0     = 0x0C0,
	//Window Buffer End Address
	rVIDW00ADD1B0   = 0x0D0,
	rVIDW00ADD1B1   = 0x0D4,
	rVIDW01ADD1B0   = 0x0D8,
	rVIDW01ADD1B1   = 0x0DC,
	rVIDW02ADD1     = 0x0E0,
	rVIDW03ADD1     = 0x0E8,
	rVIDW04ADD1     = 0x0F0,
       //Window Buffer Size
	rVIDW00ADD2     = 0x100,
	rVIDW01ADD2     = 0x104,
	rVIDW02ADD2     = 0x108,
	rVIDW03ADD2     = 0x10C,
	rVIDW04ADD2     = 0x110,
	//Indicate the Video Interrupt Control
	rVIDINTCON0     = 0x130,
	//Video Interrupt Pending
	rVIDINTCON1     = 0x134,
	//Color Key Control/Value
	rW1KEYCON0      = 0x140,
	rW1KEYCON1      = 0x144,
	rW2KEYCON0      = 0x148,
	rW2KEYCON1      = 0x14C,
	rW3KEYCON0      = 0x150,
	rW3KEYCON1      = 0x154,
	rW4KEYCON0      = 0x158,
	rW4KEYCON1      = 0x15C,
	//DithMode
	rDITHMODE       = 0x170,
       //Window Control
	rWIN0MAP        = 0x180,
	rWIN1MAP        = 0x184,
	rWIN2MAP        = 0x188,
	rWIN3MAP        = 0x18C,
	rWIN4MAP        = 0x190,
	//Window Palette Control
	rWPALCON        = 0x1A0,
	//I80/RGB Trigger Control
	rTRIGCON        = 0x1A4,
	rITUIFCON0	   = 0x1A8,

    //I80 Interface Control for Main/Sub LDI
	rI80IFCONA0     = 0x1B0,
	rI80IFCONA1     = 0x1B4,
	rI80IFCONB0     = 0x1B8,
	rI80IFCONB1     = 0x1BC,
	//I80 Interface LDI Command Cotrol
	rLDI_CMDCON0    = 0x1D0,
	rLDI_CMDCON1    = 0x1D4,
	//I80 Interface System Command Control
	rSIFCCON0       = 0x1E0,
	rSIFCCON1       = 0x1E4,
	rSIFCCON2       = 0x1E8,
	//I80 Interface LDI Command
	rLDI_CMD0       = 0x280,
	rLDI_CMD1       = 0x284,
	rLDI_CMD2       = 0x288,
	rLDI_CMD3       = 0x28C,
	rLDI_CMD4       = 0x290,
	rLDI_CMD5       = 0x294,
	rLDI_CMD6       = 0x298,
	rLDI_CMD7       = 0x29C,
	rLDI_CMD8       = 0x2A0,
	rLDI_CMD9       = 0x2A4,
	rLDI_CMD10      = 0x2A8,
	rLDI_CMD11      = 0x2AC,
	//Window Palette Data
	rW2PDATA01      = 0x300,
	rW2PDATA23      = 0x304,
	rW2PDATA45      = 0x308,
	rW2PDATA67      = 0x30C,
	rW2PDATA89      = 0x310,
	rW2PDATAAB      = 0x314,
	rW2PDATACD      = 0x318,
	rW2PDATAEF      = 0x31C,
	rW3PDATA01      = 0x320,
	rW3PDATA23      = 0x324,
	rW3PDATA45      = 0x328,
	rW3PDATA67      = 0x32C,
	rW3PDATA89      = 0x330,
	rW3PDATAAB      = 0x334,
	rW3PDATACD      = 0x338,
	rW3PDATAEF      = 0x33C,
	rW4PDATA01      = 0x340,
	rW4PDATA23      = 0x344,
	//Win0 Palette Ram Access Address(not SFR)
	W0PRAMSTART    = 0x400,
	//Win1 Palette Ram Access Address(not SFR)
	W1PRAMSTART    = 0x800
};

static volatile unsigned long *LCD_RegBase = NULL;
static volatile unsigned long *HCLK_GATE = NULL;
#define LCD_RegStartAddr 0x77100000
#define LCD_RegEndAddr  0x77100344

//LCD相关寄存器的配置
static volatile unsigned long *GPICON;
static volatile unsigned long *GPIDAT;
static volatile unsigned long *GPJCON;
static volatile unsigned long *GPJDAT;

static int LCD_Init(void)
{
    //1. 分配fb_info结构体
    s3c_lcd = framebuffer_alloc(0, NULL);

    //2.1 设置固定参数
    strcpy(s3c_lcd->fix.id, "MyLcd");
    s3c_lcd->fix.smem_len = 480*272*24/8;
    s3c_lcd->fix.type = FB_TYPE_PACKED_PIXELS;
    s3c_lcd->fix.visual = FB_VISUAL_TRUECOLOR;
    s3c_lcd->fix.line_length = 480*3;

    //2.2 设置可变参数
    s3c_lcd->var.xres = 480;
    s3c_lcd->var.yres = 272;
    s3c_lcd->var.xres_virtual = 480;
    s3c_lcd->var.yres_virtual = 272;
    s3c_lcd->var.bits_per_pixel = 24;

    //RGB 888
    s3c_lcd->var.red.offset = 16;
    s3c_lcd->var.red.length = 8;

    s3c_lcd->var.green.offset = 8;
    s3c_lcd->var.green.length = 8;

    s3c_lcd->var.blue.offset = 0;
    s3c_lcd->var.blue.length = 8;

    s3c_lcd->var.activate = FB_ACTIVATE_NOW;

    //2.3 设置操作函数
    s3c_lcd->fbops = &MyLCDOps;

    //2.4 其他设置
    s3c_lcd->pseudo_palette = pseudo_palette;
    s3c_lcd->screen_size = 480*272*24/8;

    //3. 硬件相关操作
    GPICON = ioremap(0x7F008100, 16);
    GPIDAT = GPICON + 1;
    GPJCON = ioremap(0x7F008120, 16);
    GPJDAT = GPJCON + 1;

    *GPICON = 0xAAAAAAAA;
    *GPJCON = 0xAAAAAAAA;           //for LCD

    LCD_RegBase = ioremap(LCD_RegStartAddr, LCD_RegEndAddr - LCD_RegStartAddr);
    HCLK_GATE = ioremap(0x7E00F030, 16);

    *HCLK_GATE |= (1 << 3);          //enable HCLK to LCD controller

    *(LCD_RegBase + rVIDCON0) = (13 << 6);
    *(LCD_RegBase + rVIDCON1) = 0;
    *(LCD_RegBase + rVIDCON2) = 0;

    //Time Control
    *(LCD_RegBase + rVIDTCON0) = (2 << 16) | (2 << 8) | 10;
    *(LCD_RegBase + rVIDTCON1) = (2 << 16) | (5 << 8) | 41;
    *(LCD_RegBase + rVIDTCON2) = (271 << 11) | 479;

    //window Control
    *(LCD_RegBase + rWINCON0) = (11 << 2) | (1);
    *(LCD_RegBase + rWINCON1) = 0;
    *(LCD_RegBase + rWINCON2) = 0;
    *(LCD_RegBase + rWINCON3) = 0;
    *(LCD_RegBase + rWINCON4) = 0;

    //Position
    *(LCD_RegBase + rVIDOSD0A) = 0;
    *(LCD_RegBase + rVIDOSD0B) = 0;
    *(LCD_RegBase + rVIDOSD0C) = 480*272*24/2;
    s3c_lcd->screen_base = dma_alloc_writecombine(NULL, s3c_lcd->fix.smem_len, &s3c_lcd->fix.smem_start, GFP_KERNEL);
    *(LCD_RegBase + rVIDW00ADD0B0) = s3c_lcd->screen_base;
    *(LCD_RegBase + rVIDW00ADD0B1) = 0;

    *(LCD_RegBase + rVIDW00ADD1B0) = s3c_lcd->screen_base + 480*272*24/8;
    *(LCD_RegBase + rVIDW00ADD1B1) = 0;

    *(LCD_RegBase + rVIDW00ADD2) = 480*272*24/8;

    *(LCD_RegBase +  rWPALCON) = 0x01;

    //启动LCD
    *(LCD_RegBase +  rVIDCON0) |= 0x03;

    register_framebuffer(s3c_lcd);
    return 0;
}

static void LCD_Exit(void)
{
    unregister_framebuffer(s3c_lcd);

    *(LCD_RegBase +  rVIDCON0) &= ~(0x03);
    *HCLK_GATE &= ~(1 << 3);          //disable HCLK to LCD controller

    dma_free_writecombine(NULL, s3c_lcd->fix.smem_len, s3c_lcd->screen_base, s3c_lcd->fix.smem_start);
    iounmap(LCD_RegBase);
    iounmap(HCLK_GATE);

    framebuffer_release(s3c_lcd);
}

module_init(LCD_Init);
module_exit(LCD_Exit);

MODULE_LICENSE("GPL");
