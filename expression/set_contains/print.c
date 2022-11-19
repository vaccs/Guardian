
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

struct stringtree* set_contains_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_set_contains);
	
	struct set_contains_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->element);
	
	stringtree_append_printf(tree, " in ");
	
	struct stringtree* sub = expression_print2(this->set);
	
	stringtree_append_tree(tree, sub);
	
	free_stringtree(sub);
	
	EXIT;
	return tree;
}

