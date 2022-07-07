#ifndef WRITE_H
#define WRITE_H

#include "IO/terminal.h"

void terminal_writestring(const char *data);
void terminal_write(const char *data, size_t size);

#endif
