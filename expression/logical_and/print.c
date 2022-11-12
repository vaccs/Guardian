
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void logical_and_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_logical_and);
	
	struct logical_and_expression* this = (void*) super;
	
	expression_print(this->left);
	
	printf(" && ");
	
	expression_print(this->right);
	
	EXIT;
}

