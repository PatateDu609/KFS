#include <convert/to_str.h>

char *uint8_to_str(uint8_t value, char *buffer, size_t size)
{
	return uint64_to_str(value, buffer, size);
}
