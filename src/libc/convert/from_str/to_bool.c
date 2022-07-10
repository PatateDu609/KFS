#include <convert/from_str.h>
#include <string.h>

bool str_to_bool(const char *str)
{
	if (strcmp(str, "true") == 0 || strcmp(str, "1") == 0)
		return true;
	else if (strcmp(str, "false") == 0 || strcmp(str, "0") == 0)
		return false;
	else
		return false;
}
