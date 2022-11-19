
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_string.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* has_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_has);
	
	struct has_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->object);
	
	stringtree_append_printf(tree, " has ");
	
	stringtree_append_string(tree, this->fieldname);
	
	EXIT;
	return tree;
}

