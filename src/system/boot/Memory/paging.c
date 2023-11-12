#include "mem/virtual.h"
#include "CPU/GDT.h"
#include "mem/physical.h"
#include "IO/terminal.h"

__aligned(FRAME_SIZE)
page_table_entry_conv_t first_table[1024];

__unused void finalize_paging_setup() {
}
