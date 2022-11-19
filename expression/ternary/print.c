
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* ternary_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_ternary);
	
	struct ternary_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->conditional);
	
	stringtree_append_printf(tree, " ? ");
	
	{
		struct stringtree* sub = expression_print2(this->true_case);
		stringtree_append_tree(tree, sub);
		free_stringtree(sub);
	}
	
	stringtree_append_printf(tree, " : ");
	
	{
		struct stringtree* sub = expression_print2(this->false_case);
		stringtree_append_tree(tree, sub);
		free_stringtree(sub);
	}
	
	EXIT;
	return tree;
}

