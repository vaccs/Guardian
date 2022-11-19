
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include <debug.h>

/*#include <avl/tree.h>*/

#include <pair/value/struct.h>

#include <list/value_pair/foreach.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <type/dict/struct.h>
#include <type/print.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* dict_value_print(
	struct value* super)
{
	ENTER;
	
	struct dict_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "{");
	
	bool first = true;
	
	value_pair_list_foreach(this->elements, ({
		void runme(struct value_pair* pair)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(tree, ", ");
			
			{
				struct stringtree* sub = value_print2(pair->key);
				stringtree_append_tree(tree, sub);
				free_stringtree(sub);
			}
			
			stringtree_append_printf(tree, ": ");
			
			{
				struct stringtree* sub = value_print2(pair->value);
				stringtree_append_tree(tree, sub);
				free_stringtree(sub);
			}
		}
		runme;
	}));
	
	if (first)
	{
		struct dict_type* dtype = (void*) super->type;
		
		stringtree_append_printf(tree, "<");
		
		struct stringtree* key = type_print2(dtype->key);
		stringtree_append_tree(tree, key);
		free_stringtree(key);
		
		stringtree_append_printf(tree, ": ");
		
		struct stringtree* val = type_print2(dtype->value);
		stringtree_append_tree(tree, val);
		
		stringtree_append_printf(tree, ">");
		free_stringtree(val);
	}
	
	printf("}");
	
	EXIT;
	return tree;
}

























