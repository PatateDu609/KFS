#include "IO/printk.h"
#include "IO/write.h"

int printk_putchar(char c, directive_args_t *fmt)
{
	int length = fmt->fwidth ? fmt->width : 1;
	length--;

	if (fmt->align)
	{
		terminal_write(" ", length);
		terminal_putchar(c);
	}
	else
	{
		terminal_putchar(c);
		terminal_write(" ", length);
	}
	return 1 + length;
}

int print_char(va_list *args, directive_args_t *fmt)
{
	char c = va_arg(*args, int);
	return printk_putchar(c, fmt);
}
