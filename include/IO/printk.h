#ifndef IO_PRINTK_H
#define IO_PRINTK_H

#include <stdarg.h>
#include "../libc/ctype.h"

// #define KERN_ERR "KERN_ERR"
// #define KERN_WARNING "KERN_WARNING"
// #define KERN_INFO "KERN_INFO"
// #define KERN_DEBUG "KERN_DEBUG"

int printk(const char *fmt, ...);
int vprintk(const char *fmt, va_list args);

// int pr_err(const char *fmt, ...);
// int pr_warn(const char *fmt, ...);
// int pr_info(const char *fmt, ...);
// int pr_debug(const char *fmt, ...);

#endif
