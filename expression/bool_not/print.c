
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <expression/print.h>

#include <stringtree/new.h>
#include <stringtree/prepend_printf.h>

#include "struct.h"
#include "print.h"

struct stringtree* bool_not_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_bool_not);
	
	struct bool_not_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->subexpression);
	
	stringtree_prepend_printf(tree, "!");
	
	EXIT;
	return tree;
}

