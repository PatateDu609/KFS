#include <string.h>
#include "nanoshell/shell.h"
#include "IO/printk.h"

void execute(char *command)
{
	int i;
	for (i = 0; i < COMMAND_NB; i++)
	{
		if (strcmp(commands[i].name, command) == 0)
		{
			commands[i].handler(command);
			return;
		}
	}
	printk("Unknown command: %s\n", command);
}
