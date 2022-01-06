#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int my_name(void){
    printk(KERN_INFO "Abe Johnson");
    return 0;
}

static void my_name_exit(void){

}

module_init(my_name);
module_exit(my_name_exit);