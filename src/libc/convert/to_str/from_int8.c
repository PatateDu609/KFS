#include <convert/to_str.h>

char *int8_to_str(int8_t value, char *buffer, size_t size)
{
	return int64_to_str(value, buffer, size);
}
