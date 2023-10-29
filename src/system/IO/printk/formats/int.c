#include "IO/printk.h"
#include <convert/to_str.h>

static void setup_buffer(va_list *args, uint8_t cast, char *buffer, size_t s)
{
	if (cast == PRINTK_CAST_HALFWORD)
		CAST(args, int32, buffer, s)
	else if (cast == PRINTK_CAST_DOUBLEWORD)
		CAST(args, int64, buffer, s)
	else if (cast == PRINTK_CAST_BYTE)
		CAST(args, int32, buffer, s)
	else
		CAST(args, int32, buffer, s)
}

int print_int(va_list *args, directive_args_t *fmt)
{
	char buffer[20];
	setup_buffer(args, fmt->cast, buffer, sizeof buffer);

	return printk_putstr(buffer, fmt, true);
}
