#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
 
static int len, temp;
static char *msg;
 
static ssize_t read_proc(struct file *filp,char *buf, size_t count, loff_t *offp )
{
    if (count > temp) count = temp;
    
    temp = temp - count;
    if (copy_to_user(buf, msg, count)) return -1;

    if (count == 0) temp = len;
 
    return count;
}
 
static ssize_t write_proc(struct file *filp,const char *buf, size_t count, loff_t *offp)
{
    if (copy_from_user(msg, buf, count)) return -1;
    len = count;
    temp = len;
    return count;
}
 
static const struct proc_ops proc_fops = {
proc_read:
    read_proc,
proc_write:
    write_proc
};
 
static int __init proc_init(void) {
    proc_create("proctest", 0, NULL, &proc_fops);
    msg = kmalloc(10*sizeof(char), GFP_KERNEL);

    pr_debug("Module initialized successfully\n");

    return 0;
}
 
static void __exit proc_exit(void) {
    remove_proc_entry("proctest", NULL);
    kfree(msg);
    
    pr_debug ("Module uninitialized successfully\n");
}
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nick Chi & AtriLux");
MODULE_DESCRIPTION("Linux 5.6+ change struct file_operations to struct proc_ops.");
module_init(proc_init);
module_exit(proc_exit);