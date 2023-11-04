#include "mem/virtual.h"
#include "mem/allocator.h"
#include "panic.h"

__unused void init_paging() {
	page_directory_entry_t *directory = kmalloc(1024 * sizeof(page_directory_entry_t));
	if (!directory) {
		kpanic("not enough memory to allocate page directory");
	}
}
