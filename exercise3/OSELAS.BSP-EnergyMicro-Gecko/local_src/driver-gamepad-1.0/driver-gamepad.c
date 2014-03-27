/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include "efm32gg.h"

/* Defines */
#define DRIVER_NAME "gamepad"
#define DEV_NR_COUNT 1

/* Function prototypes */

static int __init gamepad_init(void);
static void __exit gamepad_exit(void);
static int gamepad_open(struct inode* inode, struct file* filp);
static int gamepad_release(struct inode* inode, struct file* filp);
static ssize_t gamepad_read(struct file* filp, char* __user buff,
        size_t count, loff_t* offp);
static ssize_t gamepad_write(struct file* filp, char* __user buff,
        size_t count, loff_t* offp);

/* Static variables */
static dev_t device_nr;
struct cdev gamepad_cdev;
struct class* cl;

/* Module configs */
module_init(gamepad_init);
module_exit(gamepad_exit);
MODULE_DESCRIPTION("Device driver for the gamepad used in TDT4258");
MODULE_LICENSE("GPL");

static struct file_operations gamepad_fops = {
    .owner = THIS_MODULE,
    .open = gamepad_open,
    .release = gamepad_release,
    .read = gamepad_read,
    .write = gamepad_write,
};


/*
 * gamepad_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

static int __init gamepad_init(void)
{
    printk(KERN_ALERT "Attempting to load gamepad driver module\n");

    int result;

    /* Dynamically allocate device numbers */
    result = alloc_chrdev_region(&device_nr, 0, DEV_NR_COUNT, DRIVER_NAME);

    if (result < 0) {
        printk(KERN_ALERT "Failed to allocate device numbers\n");
        return -1;
    }

    /* Request access to ports */
    request_region(GPIO_PA_BASE, GPIO_IFC - GPIO_PA_BASE, DRIVER_NAME);

    /* init gpio as in previous exercises */
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;
    iowrite32(2, GPIO_PA_CTRL);
    iowrite32(0x33333333, GPIO_PC_MODEL);
    iowrite32(0xFF, GPIO_PC_DOUT);
    iowrite32(0x22222222, GPIO_EXTIPSELL);


    /* add device */
    cdev_init(&gamepad_cdev, &gamepad_fops);
    gamepad_cdev.owner = THIS_MODULE;
    cdev_add(&gamepad_cdev, device_nr, DEV_NR_COUNT);
    cl = class_create(THIS_MODULE, DRIVER_NAME);
    device_create(cl, NULL, device_nr, NULL, DRIVER_NAME);

    return 0;
}

/*
 * gamepad_exit - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit gamepad_exit(void)
{
    printk("Unloading gamepad driver\n");

    /* De-init GPIO stuff? */
    

    /* Remove device */
    device_destroy(cl, device_nr);
    class_destroy(cl);
    cdev_del(&gamepad_cdev);
    /* Dealloc the device numbers */
    unregister_chrdev_region(device_nr, DEV_NR_COUNT);
}


/*
 * gamepad_open - function called when open is called on "/dev/gp0"(?)
 *
 */

static int gamepad_open(struct inode* inode, struct file* filp)
{
    printk(KERN_INFO "Gamepad driver opened\n");
    return 0;
}

/*
 * gamepad_release - function called when closing
 *
 */

static int gamepad_release(struct inode* inode, struct file* filp)
{
    printk(KERN_INFO "Gamepad driver closed\n");
    return 0;
}

static ssize_t gamepad_read(struct file* filp, char* __user buff,
        size_t count, loff_t* offp)
{
    /* Read gpio button status and write to buff */
    uint32_t data = ioread32(GPIO_PC_DIN);
    printk(KERN_INFO "Writing %d to buffer", data);
    copy_to_user(buff, &data, 1);
    return 1;
}

static ssize_t gamepad_write(struct file* filp, char* __user buff,
        size_t count, loff_t* offp)
{
    printk(KERN_INFO "Writing to buttons doesn't make sense.");
    return 1;
}
