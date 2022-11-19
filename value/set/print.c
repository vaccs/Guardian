
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <debug.h>

#include <list/value/foreach.h>

#include <type/print.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <type/set/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* set_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_set);
	
	struct stringtree* tree = new_stringtree();
	
	struct set_value* this = (void*) super;
	
	stringtree_append_printf(tree, "{");
	
	bool first = true;
	
	value_list_foreach(this->elements, ({
		void runme(struct value* element)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(tree, ", ");
			
			struct stringtree* sub = value_print2(element);
			
			stringtree_append_tree(tree, sub);
			
			free_stringtree(sub);
		}
		runme;
	}));
	
	if (first)
	{
		struct set_type* stype = (void*) super->type;
		
		struct stringtree* sub = type_print2(stype->element_type);
		
		stringtree_append_printf(tree, "<");
		stringtree_append_tree(tree, sub);
		stringtree_append_printf(tree, ">");
		
		free_stringtree(sub);
	}
	
	stringtree_append_printf(tree, "}");
	
	EXIT;
	return tree;
}


















