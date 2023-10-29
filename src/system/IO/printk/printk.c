#include "IO/printk.h"
#include <stddef.h>
#include <string.h>
#include <convert/to_str.h>
#include "IO/write.h"
#include "utils.h"

typedef int (*fmt_func)(va_list *args, directive_args_t *fmt);

typedef struct format
{
	char s;
	fmt_func func;
} format_t;

static format_t formats[] = {
	{'%', print_percent},
	{'d', print_int},
	{'x', print_hex},
	{'o', print_octal},
	{'t', print_binary},
	{'b', print_bool},
	{'u', print_uint},
	{'s', print_string},
	{'c', print_char},
	{'p', print_pointer},
};

static void setup_fmt(const char **format, directive_args_t *fmt, va_list *args)
{
	printk_parse_fmt(format, fmt);
	if (fmt->fwidth == 1 && fmt->width == -1)
		fmt->width = va_arg(*args, int);
	if (fmt->fprecision == 1 && fmt->precision == -1)
		fmt->precision = va_arg(*args, int);
}

int vprintk(const char *format, va_list args)
{
	int ret = 0;
	if (format == NULL)
		return -1;

	if (args == NULL)
		return -1;

	if (strlen(format) == 0)
		return 0;

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			directive_args_t fmt;
			setup_fmt(&format, &fmt, (va_list *) &args);

			size_t max = sizeof(formats) / sizeof(format_t);
			for (size_t i = 0; i < max; i++)
			{
				if (fmt.type == formats[i].s)
				{
					ret += formats[i].func((va_list *) &args, &fmt);
					break;
				}
			}
		}
		else
		{
			terminal_putchar(*format);
			ret++;
			format++;
		}
	}
	return ret;
}

int printk(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	int ret = vprintk(format, args);

	va_end(args);
	return ret;
}

int vsprintf(__unused char *buffer, __unused const char *format, __unused va_list args)
{
	// TODO: Implement
	return -1;
}

int sprintf(char *buffer, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	int ret = vsprintf(buffer, format, args);

	va_end(args);
	return ret;
}

int vsnprintf(__unused char *buffer, __unused size_t size, __unused const char *format, __unused va_list args)
{
	// TODO: Implement
	return -1;
}

int snprintf(__unused char *buffer, __unused size_t size, __unused const char *format, ...)
{
	va_list args;
	va_start(args, format);

	int ret = vsnprintf(buffer, size, format, args);

	va_end(args);
	return ret;
}
