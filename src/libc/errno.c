#include <errno.h>

int __errno; // This is the global variable that is used to store the error number.
			// Accessible only in kernel space (to be implemented).

int *__errno_location(void)
{
	return &__errno;
}
