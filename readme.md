---

# 🛠️ **USB Driver Project**

This project is a **custom Linux USB driver** designed to recognize and interact with **USB mass storage devices** (e.g., pen drives). The driver uses **kernel-level programming** to detect, log, and handle USB device connections and disconnections.

---

## 📁 **Project Structure**

```
/usb_driver
 ├── include/                # Header files (if needed later)
 │    └── usb.h              # USB-related definitions (future)
 ├── usb_driver.c            # Main USB driver source code
 ├── usb_transfer.c          # USB data transfer operations (to be added)
 ├── Makefile                # Makefile to compile the kernel module
 ├── README.md               # Project documentation
 ├── LICENSE                 # License information
 └── .gitignore              # Ignored files
```

---

## 🚀 **Features**

- ✅ Detects and registers **USB mass storage devices**.  
- ✅ Displays details such as:  
  - **Vendor ID** and **Product ID**.  
  - **Number of endpoints**.  
  - Endpoint attributes and packet sizes.  
- ✅ Logs connection and disconnection events using `printk()`.  
- ✅ Supports **auto-suspend** for safe ejection handling.  
- 🛠️ **Planned feature:**  
    - **Data transfer support** using `usb_transfer.c` (future addition).

---

## 🔧 **Requirements**

- **Linux kernel headers** installed:  
```bash
sudo apt install linux-headers-$(uname -r)
```
- **GCC Compiler:**  
```bash
sudo apt install build-essential
```
- **Make:**  
```bash
sudo apt install make
```

---

## ⚙️ **Building the Driver**

1. **Compile the driver:**  
```bash
make
```

2. **Insert the driver into the kernel:**  
```bash
sudo insmod usb_driver.ko
```

3. **Check kernel logs:**  
```bash
dmesg | tail -n 50
```

---

## 🔥 **Usage Example**

1. **Plug in a USB device** (e.g., SanDisk 3.2 Gen Pen Drive).  
2. Check the logs:  
```bash
dmesg | grep "Pen i/f"
```
Example Output:  
```
[  239.320153] Pen i/f 0 now probed: (0781:5567)  
[  239.320154] ID->bNumEndpoints: 02  
[  239.320155] ID->bInterfaceClass: 08  
[  239.320156] ED[0]->bEndpointAddress: 0x81  
[  239.320157] ED[0]->bmAttributes: 0x02  
[  239.320158] ED[0]->wMaxPacketSize: 0x0200 (512)  
```

3. **List connected USB devices:**  
```bash
lsusb
```

4. **Display USB tree:**  
```bash
lsusb -t
```
Output:  
```
/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=xhci_hcd/4p, 5000M  
    |__ Port 2: Dev 4, If 0, Class=Mass Storage, Driver=usb-storage, 5000M  
```

---

## 🔥 **Planned Feature: USB Transfer Operations**

✅ The `usb_transfer.c` file will handle **data transfer operations**, including:  
- **Bulk transfer** → For large data chunks.  
- **Interrupt transfer** → For small, time-sensitive data.  
- **Control transfer** → For command-based operations.  

---

## 🛠️ **Unloading the Driver**

To unload the driver:  
```bash
sudo rmmod usb_driver
```

To clean up:  
```bash
make clean
```

---

## ⚠️ **Debugging Tips**

- Check kernel logs:  
```bash
dmesg | tail -n 100
```
- Verify module is loaded:  
```bash
lsmod | grep usb_driver
```
- Remove and reload the module if needed:  
```bash
sudo rmmod usb_driver  
sudo insmod usb_driver.ko  
```


## 📄 **License**
This project is licensed under the **GPL v2 License**.  
You are free to use, modify, and distribute this code under the terms of the GPL license.

---

✅ **Future Improvements**
- Add support for **data read/write** operations.  
- Include **error handling** and logging.  
- Expand compatibility to support other USB classes.