#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

static struct usb_device_id USB_Mouse_ID_Table[] =
{
    { USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT,
                            USB_INTERFACE_PROTOCOL_MOUSE)},
    {}
};

static struct input_dev *uk_dev;

static char *usb_buf;
static dma_addr_t *usb_buf_phy;
static int len;
static struct urb *uk_urb;

static void USB_MOUSE_AS_KEY_IRQ(struct urb *urb)
{
    //解析USB数据含义并上报
    static unsigned char pre_val = 0;
    if((pre_val & (1 << 0)) != (usb_buf[0] & (1 << 0)))
    {
        //左键发生变化
        input_event(uk_dev, EV_KEY, KEY_L, (usb_buf[0] & (1 << 0)) ? 1 : 0);
        input_sync(uk_dev);
    }

    if((pre_val & (1 << 1)) != (usb_buf[0] & (1 << 1)))
    {
        //左键发生变化
        input_event(uk_dev, EV_KEY, KEY_S, (usb_buf[0] & (1 << 1)) ? 1 : 0);
        input_sync(uk_dev);
    }

    if((pre_val & (1 << 2)) != (usb_buf[0] & (1 << 2)))
    {
        //中键发生变化
        input_event(uk_dev, EV_KEY, KEY_ENTER, (usb_buf[0] & (1 << 2)) ? 1 : 0);
        input_sync(uk_dev);
    }
    pre_val = usb_buf[0];

    //重新提交urb
    usb_submit_urb(uk_urb, GFP_KERNEL);
}

static int USB_Mouse_Probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    printk("USB mouse insert\n");

    struct usb_device *dev = interface_to_usbdev(intf);
    struct usb_host_interface *interface;
    struct usb_endpoint_descriptor *endpoint;
    int pipe;

    interface = intf->cur_altsetting;

    if(interface->desc.bNumEndpoints != 1)
        return -ENODEV;

    endpoint = &interface->endpoint[0].desc;
    if(!usb_endpoint_is_int_in(endpoint))
        return -ENODEV;

    printk("bcdUSB = %x\n", dev->descriptor.bcdUSB);
    printk("VID = %x\n", dev->descriptor.idVendor);
    printk("PID = %x\n", dev->descriptor.idProduct);

    //1. 分配一个input_dev结构体
    uk_dev = input_allocate_device();

    //2.1 能产生哪类事件
    set_bit(EV_KEY, uk_dev->evbit);
    set_bit(EV_REP, uk_dev->evbit);

    //2.2 能产生这类事件的哪些事件
    set_bit(KEY_L, uk_dev->keybit);
    set_bit(KEY_S, uk_dev->keybit);
    set_bit(KEY_ENTER, uk_dev->keybit);

    //3. 注册
    input_register_device(uk_dev);

    //  硬件相关操作
    //4.1 source---USB endpoint
    pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress);

    //4.2 长度
    len = endpoint->wMaxPacketSize;

    //4.3 目的
    //usb_buf = kmalloc(len, GFP_KERNEL);
    usb_buf = usb_alloc_coherent(dev, len, GFP_KERNEL, &usb_buf_phy);

    //使用usb request block
    uk_urb = usb_alloc_urb(0, GFP_KERNEL);

    usb_fill_int_urb(uk_urb, dev, pipe, usb_buf, len, USB_MOUSE_AS_KEY_IRQ, NULL, endpoint->bInterval);
    uk_urb->transfer_dma = usb_buf_phy;
    uk_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

    //使用urb
    usb_submit_urb(uk_urb, GFP_KERNEL);
    return 0;
}

static void USB_Mouse_Disconnect(struct usb_interface *intf)
{
    printk("USB mouse disconnect\n");
    struct usb_device *dev = interface_to_usbdev(intf);
    usb_kill_urb(uk_urb);
    usb_free_urb(uk_urb);
    usb_free_coherent(dev, len , usb_buf, usb_buf_phy);
    input_unregister_device(uk_dev);
    input_free_device(uk_dev);
}

static struct usb_driver USB_MouseAsKeyDriver =
{
    .name = "USBMouseAsKey",
    .probe = USB_Mouse_Probe,
    .disconnect = USB_Mouse_Disconnect,
    .id_table = USB_Mouse_ID_Table,
};

static int USB_MouseAsKeyInit(void)
{
    int ret_val = usb_register(&USB_MouseAsKeyDriver);

    return 0;
}

static void USB_MouseAsKeyExit(void)
{
    usb_deregister(&USB_MouseAsKeyDriver);
}

module_init(USB_MouseAsKeyInit);
module_exit(USB_MouseAsKeyExit);

MODULE_LICENSE("GPL");
