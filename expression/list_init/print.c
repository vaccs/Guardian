
#include <stdbool.h>

#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <list/expression/foreach.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* list_init_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_list_init);
	
	struct stringtree* tree = new_stringtree();
	
	struct list_init_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "[");
	
	bool first = true;
	
	expression_list_foreach(this->elements, ({
		void runme(struct expression* expression)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(tree, ", ");
				
			struct stringtree* sub = expression_print2(expression);
			stringtree_append_tree(tree, sub);
			free_stringtree(sub);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, "]");
	
	EXIT;
	return tree;
}

