
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

static const char* lookup[number_of_comparison_expression_kinds] = {
	[cek_less_than] = "<",
	[cek_less_than_equal_to] = "<=",
	[cek_equal_to] = "==",
	[cek_not_equal_to] = "!=",
	[cek_greater_than_equal_to] = ">=",
	[cek_greater_than] = ">",
};

struct stringtree* comparison_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_comparison);
	
	struct comparison_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->left);
	
	if (!lookup[this->kind])
	{
		TODO;
	}
	
	stringtree_append_printf(tree, " %s ", lookup[this->kind]);
	
	struct stringtree* sub = expression_print2(this->right);
	
	stringtree_append_tree(tree, sub);
	
	free_stringtree(sub);
	
	EXIT;
	return tree;
}










