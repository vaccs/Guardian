
#include <assert.h>

#include <debug.h>

#include <value/print.h>

#include "struct.h"
#include "print.h"

struct stringtree* literal_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_literal);
	
	struct literal_expression* this = (void*) super;
	
	value_print(this->value);
	#endif
	
	EXIT;
}

