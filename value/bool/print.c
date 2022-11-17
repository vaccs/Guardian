
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

struct stringtree* bool_value_print(
	struct value* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct bool_value* spef = (void*) super;
	
	if (spef->value)
	{
		printf("true");
	}
	else
	{
		printf("false");
	}
	#endif
	
	EXIT;
}

