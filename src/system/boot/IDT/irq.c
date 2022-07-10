#include "CPU/IDT.h"
#include "CPU/PIC.h"
#include "CPU/port.h"
#include "IO/printk.h"
#include "IO/keyboard.h"

void __keyboard_handler(void)
{
	uint8_t scancode = inb(KBD_DATA_PORT);
	unsigned char ch = getch(scancode);

	if (ch != NOT_FOUND)
		printk("%c", ch);

	pic_send_eoi(1);
}
