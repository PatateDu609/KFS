#include <convert/from_str.h>

uint32_t str_to_uint32(const char *str)
{
	return (uint32_t)str_to_int64(str);
}
