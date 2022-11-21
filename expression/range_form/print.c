
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <expression/print.h>

#include "struct.h"
#include "print.h"

struct stringtree* range_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_range_form);
	
	struct range_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "range!(");
	
	bool first = true;
	
	if (this->start)
	{
		if (first)
			first = true;
		else
			stringtree_append_printf(tree, ", ");
		
		TODO;
	}
	
	if (this->end)
	{
		if (first)
			first = true;
		else
			stringtree_append_printf(tree, ", ");
		
		struct stringtree* sub = expression_print2(this->end);
		stringtree_append_tree(tree, sub);
		free_stringtree(sub);
	}
	
	stringtree_append_printf(tree, ")");
	
	EXIT;
	return tree;
}










