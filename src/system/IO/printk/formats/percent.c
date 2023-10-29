#include "IO/printk.h"
#include "utils.h"

int print_percent(__unused va_list *args, directive_args_t *fmt)
{
	return printk_putchar('%', fmt);
}
