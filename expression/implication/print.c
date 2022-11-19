
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* implication_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_implication);
	
	struct implication_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->left);
	
	stringtree_append_printf(tree, " implies ");
	
	struct stringtree* sub = expression_print2(this->right);
	
	stringtree_append_tree(tree, sub);
	
	free_stringtree(sub);
	
	EXIT;
	return tree;
}

