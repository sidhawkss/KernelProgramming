#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/paravirt.h>
#include <linux/kallsyms.h>


unsigned long cr0;
extern unsigned long __force_order;

static void change_cr0(void);
static void return_cr0(void);

static inline void write_cr0_asm(unsigned long val){
	asm volatile("mov %0, %%cr0": "+r"(val), "+m"(__force_order));
}

static void change_cr0(void){
	write_cr0_asm(read_cr0() & ~0x10000);
}

static void return_cr0(void){
	write_cr0_asm(read_cr0() | 0x10000);
}

static int __init driver_init(void) {
   	printk(KERN_INFO "CR0 == %lx", read_cr0());
	change_cr0();
	printk(KERN_INFO "CR0 == %lx", read_cr0());
	return_cr0();
    return 0;
}

static void __exit driver_exit(void) {
    printk(KERN_ALERT "Removed!\n");
}
 
module_init(driver_init);
module_exit(driver_exit);
MODULE_LICENSE("GPL");


//
//   This article explains how to change the value of the CR0 in a LKM using ASM.
//   https://hadfiabdelmoumene.medium.com/change-value-of-wp-bit-in-cr0-when-cr0-is-panned-45a12c7e8411
//