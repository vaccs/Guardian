
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void implication_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_implication);
	
	struct implication_expression* this = (void*) super;
	
	expression_print(this->left), printf(" implies "), expression_print(this->right);
	
	EXIT;
}

