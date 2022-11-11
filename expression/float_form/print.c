
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void float_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_float_form);
	
	struct float_form_expression* this = (void*) super;
	
	printf("float!(");
	
	expression_print(this->object);
	
	printf(")");
	
	EXIT;
}

