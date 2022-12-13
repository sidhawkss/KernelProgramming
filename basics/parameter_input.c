#include <linux/module.h>
#include <linux/moduleparam.h>



int number;
int number2;
module_param(number, int, 0);
module_param(number2, int,0);


static int __init mod_init(void){
	printk("The number inputed was: [%d]\n", number);
	printk("The second number inputed was: [%d]\n", number2);
	return 0;
}

static void __exit mod_exit(void){
	pr_info("Exiting...");
}

module_init(mod_init);
module_exit(mod_exit);


MODULE_AUTHOR("SidHawks");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Parameter input");
