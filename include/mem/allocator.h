#ifndef KFS_ALLOCATOR_H
#define KFS_ALLOCATOR_H

#include <stddef.h>
#include "physical.h"

void init_bitmap(ptrdiff_t kern_size);

/**
 * Allocates one or more chunks of memory by aligning size to be a multiple of FRAME_SIZE.
 * @param size
 * @return The pointer to the first allocated page.
 *
 * @warning The caller must keep track of how much is allocated for a given call.
 */
void *kmalloc(size_t size);

/**
 * Frees a given memory page.
 * @param ptr
 */
void kfree(void *ptr);

#endif //KFS_ALLOCATOR_H
