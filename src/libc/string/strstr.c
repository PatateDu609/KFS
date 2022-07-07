#include <string.h>

char *strstr(const char *haystack, const char *needle)
{
	size_t needle_len = strlen(needle);
	size_t haystack_len = strlen(haystack);
	size_t i;
	for (i = 0; i < haystack_len - needle_len + 1; i++)
	{
		if (strncmp(haystack + i, needle, needle_len) == 0)
			return (char *)haystack + i;
	}
	return NULL;
}
