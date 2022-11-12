
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <expression/print.h>

#include "struct.h"
#include "print.h"

void bool_not_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_bool_not);
	
	struct bool_not_expression* this = (void*) super;
	
	printf("!"), expression_print(this->subexpression);
	
	EXIT;
}

