#ifndef IO_READ_H
#define IO_READ_H

#include "../libc/stdint.h"
#include <stddef.h>

#include "terminal.h"

void readline(char *buffer, size_t size);

#endif
