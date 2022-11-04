
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

void bool_value_print(
	struct value* super)
{
	ENTER;
	
	struct bool_value* spef = (void*) super;
	
	if (spef->value)
	{
		printf("true");
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

