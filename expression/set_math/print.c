
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

static const char* lookup[number_of_set_math_expression_kinds] = {
	[smek_union] = "|",
	[smek_intersect] = "&",
	[smek_difference] = "-",
	[smek_symdifference] = "^",
};

struct stringtree* set_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_set_math);
	
	struct set_math_expression* this = (void*) super;
	
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


















