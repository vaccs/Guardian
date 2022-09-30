
#include <debug.h>

#include "print.h"

void int_type_print(
	struct type* super)
{
	ENTER;
	
	struct int_type* this = (void*) super;
	
	printf("int");
	
	EXIT;
}

