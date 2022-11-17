
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <list/expression/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* list_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_list);
	
	struct list_expression* this = (void*) super;
	
	printf("[");
	
	struct expression_list* elements = this->elements;
	
	for (unsigned i = 0, n = elements->n; i < n; i++)
	{
		expression_print(elements->data[i]);
		
		if (i + 1 < n)
			printf(", ");
	}
	
	printf("]");
	#endif
	
	EXIT;
}

