#include <convert/to_str.h>

char *int16_to_str(int16_t value, char *buffer, size_t size)
{
	return int64_to_str(value, buffer, size);
}
