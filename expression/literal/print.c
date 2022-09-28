
#include <debug.h>

#include <value/print.h>

#include "struct.h"
#include "print.h"

void literal_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_literal);
	
	struct literal_expression* this = (void*) super;
	
	value_print(this->value);
	
	EXIT;
}

