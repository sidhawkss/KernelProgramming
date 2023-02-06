#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
MODULE_LICENSE("Dual BSD/GPL");

// Some implementations to work with task_struct 
// https://elixir.bootlin.com/linux/v5.15/source/include/linux/sched.h

static int start_pid_info(void){
	printk(KERN_INFO "Process %s with (PID %i) using cpu %i \n", current->comm, current->pid, current->cpu);
	return 0;
}

static void pidexit_info(void){
	printk(KERN_ALERT "Exiting...\n");

}

module_init(start_pid_info);
module_exit(pidexit_info);