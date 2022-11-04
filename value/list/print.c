
#include <stdio.h>

#include <debug.h>

#include <list/value/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void list_value_print(
	struct value* super)
{
	ENTER;
	
	struct list_value* spef = (void*) super;
	
	struct value_list* elements = spef->elements;
	
	printf("[");
	
	for (unsigned i = 0, n = elements->n; i < n; i++)
	{
		struct value* ele = elements->data[i];
		
		value_print(ele);
		
		if (i + 1 < n)
			printf(", ");
	}
	
	printf("]");
	
	EXIT;
}

