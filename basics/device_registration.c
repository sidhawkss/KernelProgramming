#include <linux/module.h>
#include <linux/fs.h>

#define NAME "NEW_DEVICE"
#define MAJORN 0


static int __init driver_init(void){
	int d = register_chrdev_region(MAJORN, 5, NAME);
	pr_info("Was registered as - [%d]",d);

	return 0;
}

static void __exit driver_exit(void){
	unregister_chrdev(MAJORN, NAME);
	pr_info("Exiting...");

}


module_init(driver_init);
module_exit(driver_exit);
MODULE_LICENSE("GPL");
