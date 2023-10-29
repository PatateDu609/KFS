#ifndef NANOSHELL_COMMANDS_H
#define NANOSHELL_COMMANDS_H

#define COMMAND_LENGTH_MAX 128

typedef struct
{
	char *name;
	void (*handler)(char *args);
    char *description;
} command_t;

void halt(char *args);
void stack(char *args);
void reboot(char *args);
void shutdown(char *args);
void clear(char *args);
void lsmmap(char *args);

#endif
