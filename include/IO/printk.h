#ifndef IO_PRINTK_H
#define IO_PRINTK_H

#include <stdarg.h>
#include <stdbool.h>
#include "../libc/ctype.h"
#include "../libc/stdint.h"
#include <stddef.h>
#include <string.h>

#define CAST(args, type, buf, s)					\
	{												\
		memset(buf, 0, s);							\
		type##_t value = va_arg(args, type##_t);	\
		type##_to_str(value, buf, s);				\
	}

#define CAST_BASE(args, type, buf, s, base)			\
	{												\
		memset(buf, 0, s);							\
		type##_t value = va_arg(args, type##_t);	\
		printk_to_str_base(value, buf, s, base);	\
	}

typedef struct
{
#define PRINTK_TYPE_DECIMAL 'd'
#define PRINTK_TYPE_UNSIGNED 'u'
#define PRINTK_TYPE_HEX 'x'
#define PRINTK_TYPE_OCTAL 'o'
#define PRINTK_TYPE_BINARY 't' // two
#define PRINTK_TYPE_BOOL 'b'
#define PRINTK_TYPE_CHAR 'c'
#define PRINTK_TYPE_STRING 's'
#define PRINTK_TYPE_POINTER 'p'
#define PRINTK_TYPE_PERCENT '%'
	char type;

	int32_t width;	   // Width of the field
	int32_t precision; // For %s, %c, %d, %u, %x, %X

#define PRINTK_CAST_WORD 0b00		// 'w' or 'W'
#define PRINTK_CAST_HALFWORD 0b10	// 'h' or 'H'
#define PRINTK_CAST_BYTE 0b01		// 'b' or 'B'
#define PRINTK_CAST_DOUBLEWORD 0b11 // 'g' or 'G'
	uint8_t cast : 2;
	uint8_t hash : 1; // prepend 0x for hexadecimal, 0 for octal, etc.

	uint8_t fwidth : 1;		// Width of the field (0 if not specified)
	uint8_t fprecision : 1; // Precision of the field (0 if not specified)

	uint8_t align : 1; // If set to 1, the field is right aligned

	// The following fields are mutually exclusive
	uint8_t zero : 1;  // If set to 1, the field is zero-padded
	uint8_t space : 1; // If set to 1, a space is inserted between the sign and the number
} directive_args_t;

// Need termcap to work (will be implemented later)
// #define KERN_ERR "KERN_ERR"
// #define KERN_WARNING "KERN_WARNING"
// #define KERN_INFO "KERN_INFO"
// #define KERN_DEBUG "KERN_DEBUG"

void printk_parse_fmt(const char **fmt_str, directive_args_t *fmt);

int printk(const char *fmt, ...);
int vprintk(const char *fmt, va_list args);

// int pr_err(const char *fmt, ...);
// int pr_warn(const char *fmt, ...);
// int pr_info(const char *fmt, ...);
// int pr_debug(const char *fmt, ...);

int print_char(va_list args, directive_args_t *fmt);
int print_percent(va_list args, directive_args_t *fmt);
int print_string(va_list args, directive_args_t *fmt);
int print_uint(va_list args, directive_args_t *fmt);
int print_int(va_list args, directive_args_t *fmt);
int print_hex(va_list args, directive_args_t *fmt);
int print_pointer(va_list arg, directive_args_t *fmt);
int print_bool(va_list arg, directive_args_t *fmt);
int print_binary(va_list arg, directive_args_t *fmt);
int print_octal(va_list arg, directive_args_t *fmt);

int printk_putchar(char c, directive_args_t *fmt);
int printk_putstr(const char *str, directive_args_t *fmt, bool integer);
void printk_to_str_base(uint64_t value, char *buffer, size_t max, char *base);

void setup_buffer_base(va_list args, uint8_t cast, char *buffer, size_t s, char *base);

#endif
