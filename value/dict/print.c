
#include <stdbool.h>

#include <assert.h>

#include <stdio.h>

#include <debug.h>

#include <avl/tree.h>

#include <pair/value/struct.h>

#include <list/value_pair/foreach.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void dict_value_print(
	struct value* super)
{
	ENTER;
	
	struct dict_value* this = (void*) super;
	
	printf("{");
	
	bool first = true;
	
	value_pair_list_foreach(this->elements, ({
		void runme(struct value_pair* pair)
		{
			if (first)
				first = false;
			else
				printf(", ");
			
			value_print(pair->key);
			
			printf(": ");
			
			value_print(pair->value);
		}
		runme;
	}));
	
	if (first)
	{
		TODO;
	}
	
	printf("}");
	
	EXIT;
}

























