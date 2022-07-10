#include <convert/from_str.h>

int16_t str_to_int16(const char *str)
{
	return (int16_t)str_to_int64(str);
}
