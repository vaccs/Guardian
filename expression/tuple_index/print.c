
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/append_printf.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* tuple_index_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_tuple_index);
	
	struct tuple_index_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->tuple);
	
	stringtree_append_printf(tree, ".%u", this->index);
	
	EXIT;
	return tree;
}

