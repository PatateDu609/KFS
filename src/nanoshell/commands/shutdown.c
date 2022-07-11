#include "nanoshell/commands.h"
#include "CPU/port.h"
#include "utils.h"

void shutdown(__unused char *args)
{
	outw(0x604, 0x2000); // QEMU specific
}
