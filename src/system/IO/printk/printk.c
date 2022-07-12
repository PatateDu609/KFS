#include "IO/printk.h"
#include <stddef.h>
#include <string.h>
#include <convert/to_str.h>
#include "IO/write.h"
#include "utils.h"

typedef int (*fmt_func)(va_list *args);

typedef struct format
{
	char s;
	fmt_func func;
} format_t;

int print_char(va_list *args)
{
	char c = va_arg(*args, int);
	terminal_putchar(c);
	return 1;
}

int print_percent(__unused va_list *args)
{
	terminal_putchar('%');
	return 1;
}

int print_string(va_list *args)
{
	const char *str = va_arg(*args, const char *);
	size_t len = strlen(str);
	terminal_write(str, len);
	return len;
}

int print_uint(va_list *args)
{
	uint32_t value = va_arg(*args, uint32_t);
	char buffer[20];
	uint32_to_str(value, buffer, 20);
	size_t len = strlen(buffer);
	terminal_write(buffer, len);
	return len;
}

int print_int(va_list *args)
{
	int32_t value = va_arg(*args, int32_t);
	char buffer[20];
	int32_to_str(value, buffer, 20);
	size_t len = strlen(buffer);
	terminal_write(buffer, len);
	return len;
}

int print_hex(va_list *args)
{
	uint32_t value = va_arg(*args, uint32_t);
	char buffer[20];

	size_t i = 0;
	while (value > 0)
	{
		uint8_t c = value & 0xF;
		if (c < 10)
		{
			buffer[i++] = '0' + c;
		}
		else
		{
			buffer[i++] = 'A' + (c - 10);
		}
		value >>= 4;
	}
	buffer[i] = '\0';
	// Reverse the string
	for (size_t j = 0; j < i / 2; j++)
	{
		char tmp = buffer[j];
		buffer[j] = buffer[i - j - 1];
		buffer[i - j - 1] = tmp;
	}

	terminal_write(buffer, i);

	return i;
}

int print_pointer(va_list *arg)
{
	terminal_writestring("0x");
	return print_hex(arg) + 2;
}

static format_t formats[] = {
	{'c', print_char},
	{'%', print_percent},
	{'s', print_string},
	{'u', print_uint},
	{'d', print_int},
	{'x', print_hex},
	{'p', print_pointer},
};

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
			size_t max = sizeof(formats) / sizeof(format_t);
			for (size_t i = 0; i < max; i++)
			{
				if (*format == formats[i].s)
				{
					ret += formats[i].func(&args);
					break;
				}
			}
		}
		else
		{
			terminal_putchar(*format);
			ret++;
		}
		format++;
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
