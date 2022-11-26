
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <pair/expression/struct.h>

#include <list/expression_pair/foreach.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* dict_init_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_dict_init);
	
	struct dict_init_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "{");
	
	bool first = true;
	
	expression_pair_list_foreach(this->elements, ({
		void runme(struct expression_pair* pair)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(tree, ", ");
			
			{
				struct stringtree* key = expression_print2(pair->key);
				stringtree_append_tree(tree, key);
				free_stringtree(key);
			}
			
			stringtree_append_printf(tree, ": ");
			
			{
				struct stringtree* value = expression_print2(pair->value);
				stringtree_append_tree(tree, value);
				free_stringtree(value);
			}
		}
		runme;
	}));
	
	if (first)
	{
		TODO;
	}
	
	stringtree_append_printf(tree, "}");
	
	EXIT;
	return tree;
}























