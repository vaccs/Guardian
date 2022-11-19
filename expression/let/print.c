
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_string.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <named/expression/struct.h>

#include <list/named_expression/foreach.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* let_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_let);
	
	struct let_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "let! ");
	
	bool first = true;
	
	named_expression_list_foreach(this->parameters, ({
		void runme(struct named_expression* ele)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(tree, ", ");
			
			stringtree_append_string(tree, ele->name);
			
			stringtree_append_printf(tree, " = ");
			
			struct stringtree* sub = expression_print2(ele->expression);
			
			stringtree_append_tree(tree, sub);
			
			free_stringtree(sub);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ": ");
	
	struct stringtree* sub = expression_print2(this->body);
	
	stringtree_append_tree(tree, sub);
	
	free_stringtree(sub);
	
	EXIT;
	return tree;
}

























