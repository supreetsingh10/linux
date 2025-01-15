#include "linux/kern_levels.h"
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/spinlock_types.h>
#include <linux/syscalls.h>
#include <net/bluetooth/bluetooth.h>
#include <net/bluetooth/hci_core.h>
#include <linux/string.h>

LIST_HEAD(hci_dev_list);
DEFINE_RWLOCK(hci_dev_list_lock);

SYSCALL_DEFINE2(romani, char*, name, int, volume) {
	struct hci_dev* hdev = NULL, *con = NULL;

	printk(KERN_INFO "Syscall called");

	read_lock(&hci_dev_list_lock);
	list_for_each_entry(hdev, &hci_dev_list, list) {
		printk(KERN_INFO "Romani found here %s", hdev->name);
		if(strcmp(hdev->name, name) == 0) {
			con = hdev;
		}
	}
	read_unlock(&hci_dev_list_lock);
	return 0;
}
