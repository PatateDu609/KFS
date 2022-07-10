#include <convert/from_str.h>

int32_t str_to_int32(const char *str)
{
	return (int32_t)str_to_int64(str);
}
