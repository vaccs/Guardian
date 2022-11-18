
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <list/type/foreach.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* lambda_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_lambda);
	
	struct stringtree* tree = new_stringtree();
	
	struct lambda_type* this = (void*) super;
	
	stringtree_append_printf(tree, "(");
	
	stringtree_append_printf(tree, "$");
	
	bool first = true;
	
	type_list_foreach(this->parameters, ({
		void runme(struct type* type)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(tree, ", ");
			
			struct stringtree* subtree = type_print2(type);
			
			stringtree_append_tree(tree, subtree);
			
			free_stringtree(subtree);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, " -> ");
	
	struct stringtree* subtree = type_print2(this->rettype);
	stringtree_append_tree(tree, subtree);
	stringtree_append_printf(tree, ")");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}













