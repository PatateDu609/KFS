#include "nanoshell/commands.h"
#include "utils.h"

void halt(__unused char *args)
{
	asm("cli; hlt");
}
