#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/device.h>


#define NAME (char *)"PLANBDEVICE"
#define MAJORN 0


dev_t device = 0;
static struct cdev struct_device;
static struct class *device_class;

static ssize_t func_read(struct file *file, char __user *buf, size_t size, loff_t *pos);
static ssize_t func_write(struct file *file, const char __user *buf, size_t size, loff_t *pos);
static int func_open(struct inode *inode, struct file *file);
static int func_release(struct inode *inode, struct file *file);
static int __init driver_ini(void);
static void __exit driver_exit(void);


static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .read    = func_read,
    .open    = func_open,
    .write   = func_write,
    .release = func_release,
};

static ssize_t func_read(struct file *file, char __user *buf, size_t size, loff_t *pos){
    pr_info("read working\n");
    return 0;
}
static ssize_t func_write(struct file *file, const char __user *buf, size_t size, loff_t *pos){
    pr_info("write working\n");
    return 0;
}
static int func_open(struct inode *inode, struct file *file){
    pr_info("open working\n");
    return 0;
}
static int func_release(struct inode *inode, struct file *file){
    pr_info("release working\n");
    return 0;
}

static int __init driver_ini(void){

    // Chardev allocation
    if((alloc_chrdev_region(&device, 0,1, NAME)) < 0){
        pr_err("Error on registration\n");
	unregister_chrdev_region(device, 1);
        return -1;
    }else{
        pr_info("Registration with success! major=[%d] minor=[%d]\n",MAJOR(device), MINOR(device));
    }

    // Chrdev struct initialization
    cdev_init(&struct_device, &fops);

    // Chrdev add
    if((cdev_add(&struct_device,device, 1)) > 0 ){
        pr_err("Error in structure add\n");
    }else{
        pr_info("Structure working\n");
    }

    // Creating struct class
    if(IS_ERR(device_class = class_create(THIS_MODULE,"PLANBDEVICE"))){
        pr_err("Cannot create the struct class\n");
        class_destroy(device_class);
        return -1;
    }else {
        pr_info("Class created!\n");
    }

   // Creating device 
    if(IS_ERR(device_create(device_class,NULL,device,NULL,"PLANBDEVICE"))){
        pr_err("Cannot create the Device 1\n");
        unregister_chrdev_region(device,1);
        return -1;
    }else{
        pr_info("Device created!\n");
        return 0;
    }

}

static void __exit driver_exit(void){
    device_destroy(device_class,device);
    class_destroy(device_class);
    unregister_chrdev_region(MAJORN, NAME);
    pr_info("Exiting...");

}


module_init(driver_ini);
module_exit(driver_exit);
MODULE_LICENSE("GPL");

// Studies based on EmbeTronicX chardev code.
// https://embetronicx.com/tutorials/linux/device-drivers/cdev-structure-and-file-operations-of-character-drivers/