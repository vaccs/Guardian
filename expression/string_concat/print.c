
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

struct stringtree* string_concat_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_string_concat);
	
	struct string_concat_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->left);
	
	stringtree_append_printf(tree, " + ");
	
	struct stringtree* sub = expression_print2(this->right);
	
	stringtree_append_tree(tree, sub);
	
	free_stringtree(sub);
	
	EXIT;
	return tree;
}

