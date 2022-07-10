#include <convert/to_str.h>

static uint64_t uint64len(uint64_t i)
{
	uint64_t len = 0;
	while (i > 0)
	{
		i /= 10;
		len++;
	}
	return len;
}

char *uint64_to_str(uint64_t value, char *buffer, size_t size)
{
	char *p = buffer;
	char *end = buffer + size;
	uint64_t tmp;
	size_t i;

	if (value == 0)
	{
		*p++ = '0';
		*p = '\0';
		return buffer;
	}

	tmp = value;
	for (i = 0; tmp > 0; i++)
		tmp /= 10;

	if (end - p < (long int)i + 1)
		return NULL;

	tmp = value;
	size_t max = uint64len(value);
	p = buffer + max - 1;
	for (i = 0; i < max; i++)
	{
		*p-- = '0' + (tmp % 10);
		tmp /= 10;
	}

	*p = '\0';

	return buffer;
}
