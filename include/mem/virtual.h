#ifndef KFS_VIRTUAL_H
#define KFS_VIRTUAL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "utils.h"

typedef union __packed {
	struct __packed {
		bool P: 1; ///< Present
		bool rw: 1; ///< Read/Write
		bool us: 1; ///< User/Supervisor
		bool pwt: 1; ///< Write-Through
		bool pcd: 1; ///< Cache disabled
		bool A: 1; ///< Accessed
		bool avl1: 1; ///< Available for OS Use
		bool PS: 1; //< Page size
		uint8_t avl2: 4; ///< Available for OS use
		uint32_t addr:20;
	} split;
	uint32_t raw;
} page_directory_entry_t;

void init_paging();

#endif //KFS_VIRTUAL_H
