#include <string.h>
#include "nanoshell/shell.h"
#include "IO/printk.h"
#include "utils.h"

#define NB_COMMANDS 7

static command_t commands[NB_COMMANDS];

void help(__unused char *arg) {
	printk("help:\n");
	for (int i = 0; i < NB_COMMANDS; i++) {
		printk("\t - %s\t%s\n", commands[i].name, commands[i].description);
	}
}

static command_t commands[NB_COMMANDS] = {
		{
				.name = "reboot",
				.handler = reboot,
				.description= "Reboots the machine (warning: works only in QEMU)",
		},
		{
				.name = "shutdown",
				.handler = shutdown,
				.description = "Shuts down the machine (warning: works only in QEMU)",
		},
		{
				.name = "halt",
				.handler = halt,
				.description = "Pauses the machine",
		},
		{
				.name = "stack",
				.handler = stack,
				.description = "Prints the current memory stack",
		},
		{
				.name = "clear",
				.handler =    clear,
				.description = "Clears the terminal",
		},
		{
				.name = "lsmmap",
				.handler = lsmmap,
				.description = "Prints the mmap entries from multiboot",
		},
		{
				.name = "help",
				.handler = help,
				.description = "Prints this help menu",
		},
};

void execute(char *command) {
	size_t i;
	size_t max = sizeof(commands) / sizeof(commands[0]);

	for (i = 0; i < max; i++) {
		if (strcmp(commands[i].name, command) == 0) {
			commands[i].handler(command);
			return;
		}
	}
	printk("Unknown command: %s\n", command);
	help(NULL);
}
