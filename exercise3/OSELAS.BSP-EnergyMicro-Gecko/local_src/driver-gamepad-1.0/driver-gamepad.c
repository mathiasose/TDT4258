/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include "efm32gg.h"

/* Defines */
#define DRIVER_NAME "gamepad"
#define DEV_NR_COUNT 1

/* Function prototypes */

static int __init gamepad_init(void);
static void __exit gamepad_exit(void);
static int gamepad_open(struct inode* inode, struct file* filp);
static int gamepad_release(struct inode* inode, struct file* filp);
static ssize_t gamepad_read(struct file* filp, char* __user buff, size_t count, loff_t* offp);
static ssize_t gamepad_write(struct file* filp, char* __user buff, size_t count, loff_t* offp);

/* Static variables */
static dev_t* device_nr;

/* Module configs */
module_init(gamepad_init);
module_exit(gamepad_exit);
MODULE_DESCRIPTION("Small module, demo only, not very useful.");
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
    result = alloc_chrdev_region(device_nr, 0, DEV_NR_COUNT, DRIVER_NAME);

    if (result < 0) {
        printk(KERN_ALERT "Failed to allocate device numbers\n");
        return -1;
    }

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

    /* Dealloc the device numbers */
    unregister_chrdev_region(device_nr, DEV_NR_COUNT);
}
