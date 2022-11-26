
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

/*#include <list/expression/foreach.h>*/

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* reduce_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_reduce_form);
	
	struct stringtree* tree = new_stringtree();
	
	struct reduce_form_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "reduce!(");
	
	{
		struct stringtree* sub = expression_print2(this->lambda);
		stringtree_append_tree(tree, sub);
		free_stringtree(sub);
	}
	
	stringtree_append_printf(tree, ", ");
	
	{
		struct stringtree* sub = expression_print2(this->list);
		stringtree_append_tree(tree, sub);
		free_stringtree(sub);
	}
	
	stringtree_append_printf(tree, ", ");
	
	{
		struct stringtree* sub = expression_print2(this->initial);
		stringtree_append_tree(tree, sub);
		free_stringtree(sub);
	}
	
	stringtree_append_printf(tree, ")");
	
	EXIT;
	return tree;
}












