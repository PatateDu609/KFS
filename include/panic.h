#ifndef LIBC_PANIC_H
#define LIBC_PANIC_H

#include "libc/errno.h"
#include "IO/printk.h"
#include "utils.h"

__noreturn
void kpanic(const char *msg, ...);

#endif
