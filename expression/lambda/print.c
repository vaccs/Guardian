
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include <list/named_type/foreach.h>

#include <named/type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_string.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <type/print.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* lambda_expression_print(
	struct expression* super)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct lambda_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "$");
	
	bool first = true;
	
	named_type_list_foreach(this->parameters, ({
		void runme(struct named_type* ntype)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(tree, ", ");
			
			if (ntype->type)
			{
				struct stringtree* sub = type_print2(ntype->type);
				stringtree_append_tree(tree, sub);
				stringtree_append_printf(tree, " ");
				free_stringtree(sub);
			}
			
			stringtree_append_string(tree, ntype->name);
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

























