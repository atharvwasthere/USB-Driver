// #include <stdio.h> Cant use them as they operate in user mode, in kernel mode we cant use them
// #include "usb_driver/include/usb.h" // NOLINT
#include <linux/module.h>  // NOLINT
#include <linux/usb.h>  // NOLINT
// #include <linux/init.h>  // NOLINT

// #include "usb_driver/include/init.h" //NOLINT



static int __init usb_skel_init(void){
    int result;
    printk(KERN_INFO "Module is iniitalisSed\n");
    return 0;
}
module_init(usb_skel_init);

static void __exit usb_skel_exit(void){
    printk(KERN_INFO "Module is exited\n");
};

module_exit(usb_skel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Atharv");
MODULE_DESCRIPTION("ABC");