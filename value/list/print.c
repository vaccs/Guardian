
#include <assert.h>
#include <stdbool.h>

#include <stdio.h>

#include <debug.h>

#include <list/value/foreach.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* list_value_print(
	struct value* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == vk_list);
	
	struct list_value* this = (void*) super;
	
	printf("[");
	
	bool first = true;
	
	value_list_foreach(this->elements, ({
		void runme(struct value* element)
		{
			if (first)
				first = false;
			else
				printf(", ");
			
			value_print(element);
		}
		runme;
	}));
	
	printf("]");
	#endif
	
	EXIT;
}

