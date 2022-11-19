
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

static const char* lookup[number_of_dict_math_expression_kinds] = {
	[dmek_union] = "|",
	[dmek_intersect] = "&",
	[dmek_difference] = "-",
	[dmek_symdifference] = "^",
};

struct stringtree* dict_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_dict_math);
	
	struct dict_math_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->left);
	
	if (!lookup[this->kind])
	{
		TODO;
	}
	
	stringtree_append_printf(tree, " %s ", lookup[this->kind]);
	
	struct stringtree* subtree = expression_print2(this->right);
	
	stringtree_append_tree(tree, subtree);
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}


















