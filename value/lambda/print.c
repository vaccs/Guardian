
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_string.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <list/parameter/foreach.h>

#include <type/print.h>

#include <expression/struct.h>
#include <expression/print.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* lambda_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_lambda);
	
	struct stringtree* tree = new_stringtree();
	
	struct lambda_value* this = (void*) super;
	
	stringtree_append_printf(tree, "$");
	
	bool first = true;
	
	parameter_list_foreach(this->parameters, ({
		void runme(struct string* name, struct type* type)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(tree, ", ");
			
			if (type)
			{
				struct stringtree* sub = type_print2(type);
				
				stringtree_append_tree(tree, sub);
				stringtree_append_printf(tree, " ");
				
				free_stringtree(sub);
			}
			
			stringtree_append_string(tree, name);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, " -> ");
	
	{
		struct stringtree* sub = type_print2(this->body->type);
		
		stringtree_append_tree(tree, sub);
		
		free_stringtree(sub);
	}
	
	stringtree_append_printf(tree, ": ");
	
	{
		struct stringtree* sub = expression_print2(this->body);
		
		stringtree_append_tree(tree, sub);
		
		free_stringtree(sub);
	}
	
	EXIT;
	return tree;
}

















