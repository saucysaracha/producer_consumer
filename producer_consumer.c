#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>

#define DEVICE_NAME "producer_consumer"

//static int dev_open(struct inode*, struct file*);
//static int dev_release(struct inode*, struct file*);
//static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
//static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

static int buffSize = 0;
module_param(buffSize,int,0);

static int prod = 0;
module_param(prod,int,0);

static int cons = 0;
module_param(cons,int,0);

static int uuid = 0;
module_param(uuid,int,0);

/*
static struct file_operations fops = {
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
}; */

static int major;

static void scan_tasks(void){
	struct task_struct* p;
	int process_counter = 0;
	int task_user_id = 0;
	
	for_each_process(p){
		++process_counter;
		task_user_id = (int)p->cred->uid.val;
		if(task_user_id == uuid){
			printk(KERN_INFO "pid: %i", p->pid);
			printk(KERN_INFO "task_user_id: %i", task_user_id);
		}
	}
	printk(KERN_INFO "Number of tasks found is: %i", process_counter);
}

static int kthread_producer(void *arg){
	//printk(KERN_INFO "In producer thread\n");
	printk(KERN_INFO "kthread Producer Created Successfully\n");
	scan_tasks();
	return 0;
}


//main
static int __init producer_consumer_init(void){
	//major = register_chrdev(0, DEVICE_NAME, &fops);
	//int ts1 = 0;
	/*if(major < 0) {
		printk(KERN_ALERT "Producer_consumer load failed\n");
		return 0;
	}*/
	//scan_tasks();
	//printk(KERN_INFO "Buffer size: %i\n", buffSize);
	//printk(KERN_INFO "uuid: %i\n", uuid);
	//create and run "thread-1"
	//ts1 =
	//kthread_run(kthread_producer, NULL, "thread-1");
	printk(KERN_INFO "CSE330 Project-1 Kernel Module Inserted\n");
	printk(KERN_INFO "Kernel module received the following inputs: UID:%i, Buffer-Size:%i, No of Producer:%i, No of Consumer:%i\n", uuid, buffSize, prod, cons);
	kthread_run(kthread_producer, NULL, "thread-1");
	return 0;
}

static void __exit producer_consumer_exit(void){
	unregister_chrdev(major, DEVICE_NAME);
	//printk(KERN_INFO "Producer_consumer module has been unloaded\n");
	printk(KERN_INFO "CSE330 Project 1 Kernel Module Removed\n");
}



module_init(producer_consumer_init);
module_exit(producer_consumer_exit);
MODULE_LICENSE("GPL");
