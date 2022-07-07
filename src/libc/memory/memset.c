#include <string.h>

void *memset(void *dest, int c, size_t n)
{
	unsigned char *p = dest;
	for (size_t i = 0; i < n; i++)
		p[i] = c;
	return dest;
}
