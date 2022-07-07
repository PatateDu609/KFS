#include <string.h>

void *memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *p = dest;
	const unsigned char *q = src;
	for (size_t i = 0; i < n; i++)
		p[i] = q[i];
	return dest;
}
