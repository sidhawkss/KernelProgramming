#include <linux/module.h>
#include <linux/symtab.h>


MODULE_LICENSE("Dual BSD/GPL");


void public_symb(void){
	pr_info("f");
}


//EXPORT_SYMBOL(public_symb);
//register_symtab(NULL);

static int driver_init(void){
	printk(KERN_INFO "Running");
	return 0;
}

static void driver_exit(void){
	printk(KERN_ALERT "Closing the module.\n");

}

module_init(driver_init);
module_exit(driver_exit);
