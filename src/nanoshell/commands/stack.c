#include "CPU/GDT.h"
#include "nanoshell/commands.h"
#include "utils.h"

void stack(__unused char *args)
{
	void *sp;
	void *sf;

	GET_STACK_POINTER(sp);
	GET_STACK_FRAME(sf);

	print_stack(sp - 16, sf + 16);
}
