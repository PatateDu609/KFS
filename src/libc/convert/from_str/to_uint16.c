#include <convert/from_str.h>

uint16_t str_to_uint16(const char *str)
{
	return (uint16_t)str_to_int64(str);
}
