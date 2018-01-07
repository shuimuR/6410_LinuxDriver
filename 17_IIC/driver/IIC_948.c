#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/fs.h>
#include <asm/uaccess.h>



/**********************************************************
 * 948 addr define
 */
//地址值为7位
static unsigned short normal_addr[] = { 0x2C, I2C_CLIENT_END };

static const struct i2c_device_id DS90UB948_ids[] =
{
    { "DS90UB948", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, DS90UB948_ids);

static int DS90UB948_probe(struct i2c_client *client,
			const struct i2c_device_id *id);
static int DS90UB948_remove(struct i2c_client *client);

static ssize_t DS90UB948_Read(struct file *file, char __user *buf, size_t size, loff_t * offset);
static ssize_t DS90UB948_Write(struct file *file, const char __user *buf, size_t size, loff_t *offset);

static int major;
static struct file_operations DS90UB948_Fops =
        {
                .owner = THIS_MODULE,
                .read = DS90UB948_Read,
                .write = DS90UB948_Write,
        };

static struct class *DS90UB948_Class;
static struct class_device *DS90UB948_Dev;


/*********************************************************
 * Driver struct
 */
static struct i2c_driver Drv948_Driver =
{
    .driver = {
		.name = "DS90UB948",
		.owner = THIS_MODULE,
	},
	.probe = DS90UB948_probe,
	.remove = DS90UB948_remove,
	.id_table = DS90UB948_ids,
    .address_list	= normal_addr,
};

static int DS90UB948_remove(struct i2c_client *client)
{
    printk("DS90UB948_remove\n");

    unregister_chrdev(major, "DS90UB948");
    device_destroy(DS90UB948_Class, MKDEV(major, 0));
    class_destroy(DS90UB948_Class);

    //i2c_detach_client(client);
    kfree(i2c_get_clientdata(client));


    return 0;
}

struct i2c_client *DS90UB948_client;

static int DS90UB948_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
    printk("DS90UB948_probe\n");

#if 0
    DS90UB948_client = kzalloc(sizeof(struct i2c_client), GFP_KERNEL);

    DS90UB948_client->addr = address;
    DS90UB948_client->adapter = adapter;
    DS90UB948_client->driver = &Drv948_Driver;
    strcpy(DS90UB948_client->name, "DS90UB948");

    i2c_attach_client(DS90UB948_client);
#endif
    if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
    //if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
    {
        printk("i2c_check_functionality return error\n");
        return -EIO;
    }

    printk("register char dev\n");
    major = register_chrdev(0, "DS90UB948", &DS90UB948_Fops);

    DS90UB948_Class = class_create(THIS_MODULE, "DS90UB948");

    DS90UB948_Dev = device_create(DS90UB948_Class, NULL, MKDEV(major, 0), NULL, "%s", "DS90UB948");			//创建类FirstDrv下的/dev/xyz节点

    return 0;
}

static ssize_t DS90UB948_Read(struct file *file, char __user *buf, size_t size, loff_t * offset)
{
    unsigned char address;
    unsigned char data;
    struct i2c_msg msg[2];
    int ret;

    if(size != 1)
    {
        printk("This driver just support read 1 byte data one time\n");
        return -EINVAL;
    }

    copy_from_user(&address, buf, 1);

    //写数据地址
    msg[0].addr = DS90UB948_client->addr;
    msg[0].buf = &address;
    msg[0].len = 1;
    msg[0].flags = 0;

    //读数据
    msg[1].addr = DS90UB948_client->addr;
    msg[1].buf = &data;
    msg[1].len = 1;
    msg[1].flags = I2C_M_RD;

    ret = i2c_transfer(DS90UB948_client->adapter, msg, 2);
    if(ret == 2)
    {
        copy_to_user(&buf[0], &data, 1);
        return 1;
    }
    else
    {
        return -EINVAL;
    }
}

/****************************************************************
 * 948 的初始化采用每次两个字节的写入，Addr_Data, Data
 * @param file
 * @param __user
 * @return
 */
static ssize_t DS90UB948_Write(struct file *file, const char __user *buf, size_t size, loff_t *offset)
{
    unsigned char val[2];
    struct i2c_msg msg[1];
    int ret;

    if(size != 2)
    {
        printk("This driver just support write Start--Addr--Data--stop \n");
        return -EINVAL;
    }

    copy_from_user(val, buf, 2);

    msg[0].addr = DS90UB948_client->addr;
    msg[0].buf = val;
    msg[0].len = 2;
    msg[0].flags = 0;

    ret = i2c_transfer(DS90UB948_client->adapter, msg, 1);
    if(ret == 1)
        return 2;
    else
        return -EINVAL;
}


static int Drv948_Init(void)
{
    printk("Drv948_Init\n");

    i2c_add_driver(&Drv948_Driver);
    return 0;
}

static void Drv948_Exit(void)
{
    printk("Drv948_Exit\n");

    i2c_del_driver(&Drv948_Driver);
}

module_init(Drv948_Init);
module_exit(Drv948_Exit);

MODULE_LICENSE("GPL");
