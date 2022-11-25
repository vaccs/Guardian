
#include <stdbool.h>
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

struct stringtree* all_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_all_form);
	
	struct stringtree* tree = new_stringtree();
	
	struct all_form_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "all!(");
	
	struct stringtree* sub = expression_print2(this->list);
	
	stringtree_append_tree(tree, sub);
	
	stringtree_append_printf(tree, ")");
	
	free_stringtree(sub);
	
	EXIT;
	return tree;
}








