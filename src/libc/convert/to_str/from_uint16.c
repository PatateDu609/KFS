#include <convert/to_str.h>

char *uint16_to_str(uint16_t value, char *buffer, size_t size)
{
	return uint64_to_str(value, buffer, size);
}
