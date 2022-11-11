
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void len_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_len_form);
	
	struct len_form_expression* this = (void*) super;
	
	printf("len(");
	
	expression_print(this->list);
	
	printf(")");
	
	EXIT;
}

