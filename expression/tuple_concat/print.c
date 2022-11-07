
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void tuple_concat_expression_print(
	struct expression* super)
{
	ENTER;
	
	struct tuple_concat_expression* this = (void*) super;
	
	expression_print(this->left);
	
	printf(" + ");
	
	expression_print(this->right);
	
	EXIT;
}

























