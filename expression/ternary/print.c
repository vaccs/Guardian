
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void ternary_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_ternary);
	
	struct ternary_expression* this = (void*) super;
	
	expression_print(this->conditional);
	
	printf(" ? ");
	
	expression_print(this->true_case);
	
	printf(" : ");
	
	expression_print(this->false_case);
	
	EXIT;
}

