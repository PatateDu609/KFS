#ifndef KFS_ALLOCATOR_H
#define KFS_ALLOCATOR_H

#include <stddef.h>
#include "physical.h"

void init_bitmap(ptrdiff_t kern_size);

/**
 * Allocates one or more chunks of memory by aligning size to be a multiple of FRAME_SIZE
 * @param size
 * @return
 */
void *kmalloc(size_t size);

#endif //KFS_ALLOCATOR_H
