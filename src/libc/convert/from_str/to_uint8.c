#include <convert/from_str.h>

uint8_t str_to_uint8(const char *str)
{
	return (uint8_t)str_to_int64(str);
}
