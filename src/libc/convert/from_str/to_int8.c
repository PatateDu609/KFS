#include <convert/from_str.h>

int8_t str_to_int8(const char *str)
{
	return (int8_t)str_to_int64(str);
}
