#include <convert/to_str.h>

static size_t int64len(int64_t i)
{
	size_t len = 0;
	if (i < 0)
	{
		len++;
		i = -i;
	}
	while (i > 0)
	{
		i /= 10;
		len++;
	}
	return len;
}

char *int64_to_str(int64_t value, char *buffer, size_t size)
{
	char *p = buffer;
	char *end = buffer + size;
	int64_t tmp;
	size_t i;

	if (value == 0)
	{
		*p++ = '0';
		*p = '\0';
		return buffer;
	}

	tmp = value;
	for (i = 0; tmp > 0; i++)
	{
		tmp /= 10;
	}

	if (end - p < (long int)i + 1)
	{
		return NULL;
	}

	size_t max = int64len(value);
	if (value < 0)
	{
		*p++ = '-';
		value = -value;
	}

	tmp = value;
	p = buffer + max - 1;
	for (i = 0; i < max; i++)
	{
		*p-- = '0' + (tmp % 10);
		tmp /= 10;
	}

	*p = '\0';

	return buffer;
}
