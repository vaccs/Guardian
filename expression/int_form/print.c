
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void int_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_int_form);
	
	struct int_form_expression* this = (void*) super;
	
	printf("int!(");
	
	expression_print(this->object);
	
	printf(")");
	
	EXIT;
}

