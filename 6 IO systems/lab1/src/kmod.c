#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/seq_file.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("IP-13");


#define BUFFER_SIZE 256


static dev_t first;
static struct cdev c_dev;
static struct class *cl;
static struct proc_dir_entry *in_proc;

static size_t space_buffer[BUFFER_SIZE] = {0};
static size_t space_buffer_size = 0;


static int my_dev_uevent(struct device *dev, struct kobj_uevent_env *env) {
	add_uevent_var(env, "DEVMODE=%#o", 0777);
}


size_t count_spaces(char* str, size_t size) {
    size_t num_of_spaces = 0;
    
    for (size_t i = 0; i < size; i++) {
        if (str[i] == ' ') {
            num_of_spaces++;
        }
    }
    
    return num_of_spaces;
}


static ssize_t dev_write(struct file *f, const char __user *buf, size_t len, loff_t *off) {
    char str[BUFFER_SIZE] = {0};
    
    if (copy_from_user(str, buf, len) != 0) {
    	return -EFAULT;
    }
    
    space_buffer[space_buffer_size++] = count_spaces(str, len);
    
    return len;
}


static ssize_t dev_read(struct file *f, char __user *buf, size_t len, loff_t *off) {
	printk(KERN_INFO "dev_read is invoked\n");

    for(size_t i = 0; i < space_buffer_size; i++) {
        printk(KERN_INFO "%zu\n", space_buffer[i]);
    }
    
    return 0;
}


static const struct file_operations dev_ops = {
	.read = dev_read,
	.write = dev_write
};


static ssize_t proc_read(struct file *f, char __user *buf, size_t len, loff_t *off) {
    char s[BUFFER_SIZE] = {0};
    char try[10] = {0};
    size_t read = 0;
    size_t count = 0;
    
    if (space_buffer_size == 0) {
        return 0;
    }
    
    while (read < *off) {
        read += sprintf(try, "%zu\n", space_buffer[count++]);
        	
        if (count == space_buffer_size) {
            break;
        }
    }	
    
    read = 0;
    
    while (count < space_buffer_size) {
        size_t l = sprintf(try, "%zu\n", space_buffer[count]);
        
        if (l < len - read && l < BUFFER_SIZE - read) {
            sprintf(&s[read], "%zu\n", space_buffer[count++]);
            read += l;
        }
        else {
            break;
        }
    }
    
    if (copy_to_user(buf, s, read) != 0) {
        printk(KERN_ERR "proc_read error");
        return -EFAULT;
    }
    
    *off = read;
    
    return read;
    
}


static const struct proc_ops proc_ops = {
	.proc_read = proc_read
};


static int __init mod_init(void) {
    printk(KERN_INFO "kmod init\n");
    
    if (alloc_chrdev_region(&first, 0 , 1, "IP-13") < 0) {
        return -EFAULT;
    }
    
    if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL) {
        unregister_chrdev_region(first, 1);
        return -EFAULT;
    }
    
    cl->dev_uevent = my_dev_uevent;
    
    if (device_create(cl, NULL, first, NULL, "VAR4") == NULL) {
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -EFAULT;
    }
    
    cdev_init(&c_dev, &dev_ops);
    
    if (cdev_add(&c_dev, first, 1) < 0) {
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -EFAULT;
    }
    
    if ((in_proc = proc_create("VAR4", 0777, NULL, &proc_ops)) == NULL) {
        cdev_del(&c_dev);
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -EFAULT;
    }
    
    return 0;
}


static void __exit mod_exit(void) {
    cdev_del(&c_dev);
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    remove_proc_entry("VAR4", NULL);
    
    printk(KERN_INFO "kmod exit\n");
}


module_init(mod_init);
module_exit(mod_exit);


