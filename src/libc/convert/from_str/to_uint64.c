#include <convert/from_str.h>

uint64_t str_to_uint64(const char *str)
{
	uint64_t result = 0;

	while (*str)
	{
		if (*str < '0' || *str > '9')
			return 0;

		result *= 10;
		result += *str - '0';
		str++;
	}
	return result;
}
