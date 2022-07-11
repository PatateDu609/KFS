#include "nanoshell/commands.h"
#include "CPU/port.h"
#include "utils.h"
#include <stdint.h>


void reboot(__unused char *args)
{
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);

loop:
	asm volatile("hlt");
	goto loop;
}
