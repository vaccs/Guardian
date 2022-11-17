
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <list/expression/foreach.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* set_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_set);
	
	struct set_expression* this = (void*) super;
	
	printf("{");
	
	bool first = true;
	
	expression_list_foreach(this->elements, ({
		void runme(struct expression* element)
		{
			if (first)
				first = false;
			else
				printf(", ");
			
			expression_print(element);
		}
		runme;
	}));
	
	if (first)
	{
		TODO;
	}
	
	printf("}");
	#endif
	
	EXIT;
}
















