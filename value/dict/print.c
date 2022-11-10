
#include <assert.h>

#include <stdio.h>

#include <debug.h>

#include <avl/tree.h>

#include <pair/value/struct.h>

/*#include <list/value_pair/struct.h>*/

#include "../print.h"

#include "struct.h"
#include "print.h"

void dict_value_print(
	struct value* super)
{
	ENTER;
	
	struct dict_value* this = (void*) super;
	
	printf("{");
	
	if (this->tree->head)
	{
		for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		{
			struct value_pair* ele = node->item;
			
			value_print(ele->first);
			
			printf(": ");
			
			value_print(ele->second);
			
			if (node->next)
				printf(", ");
		}
	}
	else
	{
		TODO;
	}
	
	printf("}");
	
	EXIT;
}

























