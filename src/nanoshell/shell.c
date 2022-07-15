#include <string.h>
#include "nanoshell/shell.h"
#include "IO/printk.h"

static command_t commands[] = {
	{ "reboot", reboot },
	{ "shutdown", shutdown },
	{ "halt", halt },
	{ "stack", stack },
	{ "clear", clear },
	{ "lsmmap", lsmmap },
};

void execute(char *command)
{
	size_t i;
	size_t max = sizeof(commands) / sizeof(commands[0]);

	for (i = 0; i < max; i++)
	{
		if (strcmp(commands[i].name, command) == 0)
		{
			commands[i].handler(command);
			return;
		}
	}
	printk("Unknown command: %s\n", command);
}
