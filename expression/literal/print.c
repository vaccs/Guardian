
#include <assert.h>

#include <debug.h>

#include <value/print.h>

#include "struct.h"
#include "print.h"

struct stringtree* literal_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_literal);
	
	struct literal_expression* this = (void*) super;
	
	struct stringtree* tree = value_print2(this->value);
	
	EXIT;
	return tree;
}

