#ifndef NANOSHELL_COMMANDS_H
#define NANOSHELL_COMMANDS_H

#define COMMAND_LENGTH_MAX 256

#define COMMAND_NB 4
#define HALT_COMMAND "halt"
#define STACK_COMMAND "stack"
#define REBOOT_COMMAND "reboot"
#define SHUTDOWN_COMMAND "shutdown"

typedef struct
{
	char *name;
	void (*handler)(char *args);
} command_t;

extern command_t commands[COMMAND_NB];

void halt(char *args);
void stack(char *args);
void reboot(char *args);
void shutdown(char *args);

#endif
