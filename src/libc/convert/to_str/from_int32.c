#include <convert/to_str.h>

char *int32_to_str(int32_t value, char *buffer, size_t size)
{
	return int64_to_str(value, buffer, size);
}
