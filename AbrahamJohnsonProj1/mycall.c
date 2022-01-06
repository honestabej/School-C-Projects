#include <linux/syscalls.h>
#include <linux/kernel.h>

SYSCALL_DEFINE0(mycall){
    printk(KERN_INFO "\n This is the new system call Abe Johnson implemented \n");
    return 0;
}