#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/proc_fs.h>

#define MAJORN 0

dev_t device = 0;
static struct cdev struct_device;
static struct class *device_class;

// Functions prototypes 
static ssize_t func_read(struct file *file, char __user *buf, size_t size, loff_t *pos);
static ssize_t func_write(struct file *file, const char __user *buf, size_t size, loff_t *pos);
static int func_open(struct inode *inode, struct file *file);
static int func_release(struct inode *inode, struct file *file);
static int __init driver_ini(void);
static void __exit driver_exit(void);
static long ioctl_test(struct file *filep, unsigned int cmd, unsigned long arg);
static int open_proc(struct inode *inode, struct file *file);

static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .read    = func_read,
    .open    = func_open,
    .write   = func_write,
	.unlocked_ioctl = ioctl_test,
    .release = func_release,
};
static struct proc_ops proc_fops = {
    .proc_open = open_proc
};

static ssize_t func_read(struct file *file, char __user *buf, size_t size, loff_t *pos){
    pr_info("read\n");
    return 0;
}
static ssize_t func_write(struct file *file, const char __user *buf, size_t size, loff_t *pos){
    pr_info("write\n");
    return 0;
}
static int func_open(struct inode *inode, struct file *file){
    pr_info("open\n");
    return 0;
}
static int func_release(struct inode *inode, struct file *file){
    pr_info("release\n");
    return 0;
}
static long ioctl_test(struct file *filep, unsigned int cmd, unsigned long arg){
	return 0;
}

static int open_proc(struct inode *inode, struct file *file){
    pr_info("Proc called!\t");
    return 0;
}

static int __init driver_ini(void){
    // Chardev allocation
    if((alloc_chrdev_region(&device, 0,1, "PLANBDEVICE")) < 0){
        pr_err("Error on registration\n");
        return -1;
    }else{
        pr_info("Registration with success! major=[%d] minor=[%d]\n",MAJOR(device), MINOR(device));
    }

    // Chrdev struct initialization
    cdev_init(&struct_device, &fops);

    // Chrdev add
    if((cdev_add(&struct_device,device, 1)) < 0 ){
        pr_err("[!]Cannot add!\n");
		unregister_chrdev_region(device,1);
		return -1;
    }else{
        pr_info("[*]Structure Added\n");
    }

    // Creating struct class
    if(IS_ERR(device_class = class_create(THIS_MODULE,"PLANBDEVICE"))){
        pr_err("[!]Cannot create the struct class\n");
		unregister_chrdev_region(device,1);
		return -1;
    }else {
        pr_info("[*]Class created!\n");
    }

   // Creating device 
    if(IS_ERR(device_create(device_class,NULL,device,NULL,"PLANBDEVICE"))){
        pr_err("Cannot create the Device 1\n");
        class_destroy(device_class);
    }
	pr_info("[*]Device created!\n");

	// proc cration
    parent = proc_mkdir("nprocdir",NULL);
	proc_create("planb_proc",0666,parent,&proc_fops);

    return 0;
}

static void __exit driver_exit(void){
    device_destroy(device_class,device);
    class_destroy(device_class);
	cdev_del(&struct_device);
    unregister_chrdev_region(device,1);
    proc_remove(parent);
    pr_alert("Exiting...");
}

module_init(driver_ini);
module_exit(driver_exit);
MODULE_LICENSE("GPL");

// Studies based on EmbeTronicX chardev code.
// https://embetronicx.com/tutorials/linux/
