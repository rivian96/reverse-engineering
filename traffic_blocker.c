#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rahul Project");
MODULE_DESCRIPTION("Simple Netfilter Traffic Blocker");

static struct nf_hook_ops nfho;
static int block_traffic = 0;

// ---------------- Netfilter Hook Function ----------------
static unsigned int traffic_hook(void *priv,
                                 struct sk_buff *skb,
                                 const struct nf_hook_state *state)
{
    if (block_traffic == 1) {
        printk(KERN_INFO "Blocking packet\n");
        return NF_DROP;
    }

    return NF_ACCEPT;
}

// ---------------- procfs Write Function ----------------
static ssize_t proc_write(struct file *file,
                          const char __user *buffer,
                          size_t count,
                          loff_t *f_pos)
{
    char buf[2];

    if (copy_from_user(buf, buffer, 1))
        return -EFAULT;

    buf[1] = '\0';

    if (buf[0] == '1')
        block_traffic = 1;
    else
        block_traffic = 0;

    printk(KERN_INFO "block_traffic set to %d\n", block_traffic);
    return count;
}

// ---------------- procfs Operations ----------------
static const struct proc_ops proc_file_ops = {
    .proc_write = proc_write,
};

// ---------------- Module Init ----------------
static int __init start_module(void)
{
    // Create /proc/block_traffic
    proc_create("block_traffic", 0666, NULL, &proc_file_ops);

    // Register Netfilter Hook
    nfho.hook = traffic_hook;
    nfho.hooknum = NF_INET_PRE_ROUTING;  // Incoming packets
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho);

    printk(KERN_INFO "Traffic blocker module loaded.\n");
    return 0;
}

// ---------------- Module Exit ----------------
static void __exit end_module(void)
{
    remove_proc_entry("block_traffic", NULL);
    nf_unregister_net_hook(&init_net, &nfho);

    printk(KERN_INFO "Traffic blocker module unloaded.\n");
}

module_init(start_module);
module_exit(end_module);
