#include <ctype.h>

int isprint(int c)
{
	return (c >= ' ' && c <= '~');
}
