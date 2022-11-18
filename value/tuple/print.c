
#include <stdbool.h>
#include <assert.h>

#include <stdio.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <list/value/foreach.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* tuple_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_tuple);
	
	struct stringtree* tree = new_stringtree();
	
	struct tuple_value* this = (void*) super;
	
	stringtree_append_printf(tree, "(");
	
	bool first = true;
	bool second = true;
	
	value_list_foreach(this->subvalues, ({
		void runme(struct value* subvalue)
		{
			if (first)
				first = false;
			else
			{
				stringtree_append_printf(tree, ", ");
				
				second = false;
			}
			
			struct stringtree* subtree = value_print2(subvalue);
			
			stringtree_append_tree(tree, subtree);
			
			free_stringtree(subtree);
		}
		runme;
	}));
	
	if (second)
	{
		stringtree_append_printf(tree, ", ");
	}
	
	stringtree_append_printf(tree, ")");
	
	EXIT;
	return tree;
}















