#include <linux/module.h>
#include <linux/moduleparam.h>
MODULE_LICENSE("Dual BSD/GPL");

// to use the params you need to do:
// sudo insmod driver.ko times=10 word=test
//

static int times;
static char *word;
module_param(times, int, 0);
MODULE_PARM_DESC(times,"Used in loop to count the repetition time.");
module_param(word, charp, 0);
MODULE_PARM_DESC(word, "The world that will be returned.");


static int __init driver_init(void){
	printk("Repeating [%d] times\n", times);
	while(times){
		printk("WORD= %s\n", word);
		times--;
	}	

	return 0;
}

static void __exit driver_exit(void){
	pr_info("Exiting...");
}


module_init(driver_init);
module_exit(driver_exit);
