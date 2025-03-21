// #include <stdio.h> Cant use them as they operate in user mode, in kernel mode we cant use them
// #include "usb_driver/include/usb.h" // NOLINT
#include <linux/module.h>  // NOLINT
#include <linux/usb.h>     // NOLINT
// #include <linux/init.h>  // NOLINT
// #include "usb_driver/include/init.h" //NOLINT

// making a usb device id skel table to help connecting using prod_id & vend_id
// note these numbers are in hexadecimal format 

static struct usb_device *device;

static struct usb_device_id skel_table[] = {
    {USB_DEVICE(0x0781, 0x5567)},  // USB_DEVICE -> accepts vend,prod ids as args
    {}                              // Termination entry
};
MODULE_DEVICE_TABLE(usb, skel_table);

static int skel_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    // usb interface is used to get us 2 things a) host interface  b) endpoint descriptor
    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;
    int i;

    iface_desc = interface->cur_altsetting;

    printk(KERN_INFO "Pen i/f %d now probed: (%04X:%04X)\n",
           iface_desc->desc.bInterfaceNumber,
           id->idVendor, id->idProduct);

    printk(KERN_INFO "ID->bNumEndpoints: %02X\n", iface_desc->desc.bNumEndpoints);
    printk(KERN_INFO "ID->bInterfaceClass: %02X\n", iface_desc->desc.bInterfaceClass);

    for (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
        endpoint = &iface_desc->endpoint[i].desc;
        printk(KERN_INFO "ED[%d]->bEndpointAddress: 0x%02X\n", i, endpoint->bEndpointAddress);
        printk(KERN_INFO "ED[%d]->bmAttributes: 0x%02X\n", i, endpoint->bmAttributes);
        printk(KERN_INFO "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
               i, endpoint->wMaxPacketSize, endpoint->wMaxPacketSize);
    }

    device = usb_get_dev(interface_to_usbdev(interface));
    return 0;
}

static void skel_disconnect(struct usb_interface *interface) {
    usb_put_dev(device);
    printk(KERN_INFO "Pen Drive removed\n");
}

static struct usb_driver skel_driver = {  
    .name = "usb_driver",                 // Finds the name attribute first and places it before doing anything else 
    .probe = skel_probe,
    .disconnect = skel_disconnect,
    .id_table = skel_table,
    .supports_autosuspend = 1             // Used when we force eject the pen drive
};

int __init usb_skel_init(void) {
    int result;

    // When module is initialized -> it will try to register the pen drive attached 
    result = usb_register(&skel_driver);

    if (result < 0) {
        pr_err("usb registration failed with %s\n", skel_driver.name);
        return -1;
    }

    printk(KERN_INFO "Module is initialized\n");
    return 0;
}
module_init(usb_skel_init);

static void __exit usb_skel_exit(void) {
    usb_deregister(&skel_driver);  // Deregister the device
    printk(KERN_INFO "Module is exited\n");
}
module_exit(usb_skel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Atharv");
MODULE_DESCRIPTION("ABC");
