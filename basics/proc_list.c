#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>


static int __init mod_init(void){
	struct task_struct *task;

	printk("...Process list...\n");
	for_each_process(task){
		printk(" %s\n", task->comm);
	}
        return 0;
}

static void __exit mod_exit(void){
        pr_info("Exiting...\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_AUTHOR("SidHawks");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listing process");
