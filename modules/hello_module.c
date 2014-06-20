#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
//MODULE_DESCRIPTION("Learn Linux Modules");
//MODULE_AUTHOR("Tyler Lee");

static int __init hello_init(void) {
	printk(KERN_ALERT "Hello, world\n");
	return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO"Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
