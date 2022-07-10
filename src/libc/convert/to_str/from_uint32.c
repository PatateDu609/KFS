#include <convert/to_str.h>

char *uint32_to_str(uint32_t value, char *buffer, size_t size)
{
	return uint64_to_str(value, buffer, size);
}
