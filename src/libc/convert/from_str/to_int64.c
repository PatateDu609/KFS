#include <convert/from_str.h>

int64_t str_to_int64(const char *str)
{
	int64_t result = 0;
	int64_t sign = 1;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	while (*str)
	{
		if (*str < '0' || *str > '9')
			break ;

		result *= 10;
		result += *str - '0';
		str++;
	}

	return result * sign;
}
