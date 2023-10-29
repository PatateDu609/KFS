#include "IO/printk.h"
#include "IO/write.h"
#include <string.h>

static int printk_get_length(const char *str, directive_args_t *fmt, bool integer, int *real) {
	int len = (int) strlen(str);

	*real = len;
	if (fmt->fprecision && fmt->precision < len)
		*real = fmt->precision;

	if (fmt->fprecision && fmt->precision <= 0 && (!integer || !strcmp(str, "0")))
		return 0;

	if (fmt->fwidth && fmt->width > len)
		len = fmt->width;
	return len;
}

int printk_putstr(const char *str, directive_args_t *fmt, bool integer) {
	int real;
	int len = printk_get_length(str, fmt, integer, &real);
	if (len == 0)
		return 0;

	char *pad = (integer && fmt->zero) ? "0" : " ";
	if (*pad == '0')
		fmt->align = 1;

	if (fmt->align) {
		for (int i = 0; i < fmt->width - real; i++)
			terminal_write(pad, 1);
		terminal_write(str, real);
	} else {
		terminal_write(str, real);
		for (int i = 0; i < fmt->width - real; i++)
			terminal_write(pad, 1);
	}
	return len;
}

int print_string(va_list *args, directive_args_t *fmt) {
	const char *str = va_arg(*args, const char *);
	return printk_putstr(str, fmt, false); // false = value is not an integer
}
