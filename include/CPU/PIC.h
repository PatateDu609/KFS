#ifndef CPU_PIC_H
#define CPU_PIC_H

#include "../libc/stdint.h"

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

void pic_send_eoi(uint8_t irq);

#endif
