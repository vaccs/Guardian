
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

struct stringtree* isabspath_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_isabspath_form);
	
	struct stringtree* tree = new_stringtree();
	
	struct isabspath_form_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "isabspath!(");
	
	struct stringtree* sub = expression_print2(this->path);
	
	stringtree_append_tree(tree, sub);
	
	stringtree_append_printf(tree, ")");
	
	free_stringtree(sub);
	
	EXIT;
	return tree;
}

