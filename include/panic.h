#ifndef LIBC_PANIC_H
#define LIBC_PANIC_H

#include "libc/errno.h"
#include "IO/printk.h"
#include "utils.h"

__noreturn
void kpanic(const char *msg, ...);

#define ASSERT(cond, msg) __assert((cond), STR(cond), msg)
void __assert(bool cond, const char *cond_str, const char *msg);

#endif
