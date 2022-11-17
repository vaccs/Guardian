
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <pair/expression/struct.h>

#include <list/expression_pair/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* dict_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_dict);
	
	struct dict_expression* this = (void*) super;
	
	struct expression_pair_list* elements = this->elements;
	
	printf("{");
	
	if (elements->n)
	{
		for (unsigned i = 0, n = elements->n; i < n; i++)
		{
			expression_print(elements->data[i]->key);
			
			printf(": ");
			
			expression_print(elements->data[i]->value);
			
			if (i + 1 < n)
				printf(", ");
		}
	}
	else
	{
		TODO;
	}
	
	printf("}");
	#endif
	
	EXIT;
}























