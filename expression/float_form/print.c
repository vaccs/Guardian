
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

struct stringtree* float_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_float_form);
	
	struct stringtree* tree = new_stringtree();
	
	struct float_form_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "float!(");
	
	struct stringtree* subtree = expression_print2(this->object);
	
	stringtree_append_tree(tree, subtree);
	
	stringtree_append_printf(tree, ")");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}

