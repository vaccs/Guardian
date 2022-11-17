
#include <stdbool.h>

#include <assert.h>

#include <stdio.h>

#include <debug.h>

#include <avl/tree.h>

#include <pair/value/struct.h>

#include <list/value_pair/foreach.h>

#include <type/dict/struct.h>
#include <type/print.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* dict_value_print(
	struct value* super)
{
	ENTER;
	
	TODO;
	#if 0
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
		struct dict_type* dtype = (void*) super->type;
		
		printf("<"), type_print(dtype->key), printf(": "), type_print(dtype->value), printf(">");
	}
	
	printf("}");
	#endif
	
	EXIT;
}

























