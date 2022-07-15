#include "nanoshell/commands.h"
#include "utils.h"
#include "IO/terminal.h"

void clear(__unused char *args)
{
	terminal_clear();
}
