
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <debug.h>

#include <list/value/foreach.h>

#include <type/print.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void set_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_set);
	
	struct set_value* this = (void*) super;
	
	printf("{");
	
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
	
	if (first)
	{
		printf("<"), type_print(super->type), printf(">");
	}
	
	printf("}");
	
	EXIT;
}


















