#include "panic.h"
#include "IO/printk.h"

void kpanic(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);

	vprintk(msg, args);

	va_end(args);
	while (1) {
		asm volatile("cli; hlt");
	}

	__unreachable
}

void __assert(bool cond, const char *cond_str, const char *msg) {
	if (cond) {
		return ;
	}

	kpanic("assert failed: %s: %s\n", cond_str, msg);

	__unreachable;
}
