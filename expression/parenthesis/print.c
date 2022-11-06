
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <expression/print.h>

#include "struct.h"
#include "print.h"

void parenthesis_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_parenthesis);
	
	struct parenthesis_expression* this = (void*) super;
	
	printf("(");
	
	expression_print(this->expression);
	
	printf(")");
	
	EXIT;
}

