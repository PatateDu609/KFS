#include "CPU/IDT.h"
#include "CPU/PIC.h"
#include "CPU/port.h"
#include "IO/write.h"

void __keyboard_handler(void)
{
	uint8_t scancode = inb(KBD_DATA_PORT);

	pic_send_eoi(1);
}
