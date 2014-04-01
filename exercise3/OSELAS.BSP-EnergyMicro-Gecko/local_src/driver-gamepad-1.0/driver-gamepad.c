/*
 * This is a character device driver for the custom gamepad used int the
 * TDT4258 course at NTNU.
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
#include <linux/interrupt.h>
#include "efm32gg.h"

/* Defines */
#define DRIVER_NAME "gamepad"
#define DEV_NR_COUNT 1
#define GPIO_EVEN_IRQ_LINE 17
#define GPIO_ODD_IRQ_LINE 18

/* Function prototypes */

static int __init gamepad_init(void);
static void __exit gamepad_exit(void);
static int gamepad_open(struct inode*, struct file*);
static int gamepad_release(struct inode*, struct file*);
static ssize_t gamepad_read(struct file*, char* __user, size_t, loff_t*);
static ssize_t gamepad_write(struct file*, char* __user, size_t, loff_t*);
static irqreturn_t gpio_interrupt_handler(int, void*, struct pt_regs*);

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


/* Interrupt handler */

irqreturn_t gpio_interrupt_handler(int irq, void* dev_id, struct pt_regs* regs)
{
    return IRQ_HANDLED;
}

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
    request_mem_region(GPIO_PA_BASE, GPIO_IFC - GPIO_PA_BASE, DRIVER_NAME);
    //ioremap_nocache(GPIO_PA_BASE, GPIO_IFC - GPIO_PA_BASE);

    /* Init gpio as in previous exercises.
     * For portability, these writes should be performed with a base address
     * obtained from the ioremap_nocache call above and an offset. What we are
     * doing below is possible since we're not using virtual memory.
     */
    iowrite32(0x33333333, GPIO_PC_MODEL);
    iowrite32(0xFF, GPIO_PC_DOUT);
    iowrite32(0x22222222, GPIO_EXTIPSELL);

    /* Setup for interrupts */
    request_irq(GPIO_EVEN_IRQ_LINE, (irq_handler_t)gpio_interrupt_handler, 0, DRIVER_NAME, &gamepad_cdev);
    request_irq(GPIO_ODD_IRQ_LINE, (irq_handler_t)gpio_interrupt_handler, 0, DRIVER_NAME, &gamepad_cdev);
    

    /* add device */
    cdev_init(&gamepad_cdev, &gamepad_fops);
    gamepad_cdev.owner = THIS_MODULE;
    cdev_add(&gamepad_cdev, device_nr, DEV_NR_COUNT);
    cl = class_create(THIS_MODULE, DRIVER_NAME);
    device_create(cl, NULL, device_nr, NULL, DRIVER_NAME);

    /* Actually enable interrupts */
    iowrite32(0xFF, GPIO_EXTIFALL);
    iowrite32(0x00FF, GPIO_IEN);
    iowrite32(0xFF, GPIO_IFC);

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

    /* Free irq */
    free_irq(GPIO_EVEN_IRQ_LINE, &gamepad_cdev);
    free_irq(GPIO_ODD_IRQ_LINE, &gamepad_cdev);

    /* De-init GPIO stuff? */
    release_mem_region(GPIO_PA_BASE, GPIO_IFC - GPIO_PA_BASE);

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

/*
 * gamepad_read - reads current button status from GPIO_PC_DIN
 *
 * Returns a decimal number representing the
 * bitstring of buttons pushed.
 */

static ssize_t gamepad_read(struct file* filp, char* __user buff,
        size_t count, loff_t* offp)
{
    /* Read gpio button status and write to buff */
    uint32_t data = ioread32(GPIO_PC_DIN);
    copy_to_user(buff, &data, 1);
    return 1;
}

static ssize_t gamepad_write(struct file* filp, char* __user buff,
        size_t count, loff_t* offp)
{
    printk(KERN_INFO "Writing to buttons doesn't make sense.");
    return 1;
}
