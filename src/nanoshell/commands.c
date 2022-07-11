#include "nanoshell/shell.h"

command_t commands[] = {
	{ "reboot", reboot },
	{ "shutdown", shutdown },
	{ "halt", halt },
	{ "stack", stack },
};
