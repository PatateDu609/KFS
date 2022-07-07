#include <ctype.h>

int isgraph(int c)
{
	return isprint(c) && c != ' '; // isprint(c) cannot return other spaces than ' '
}
