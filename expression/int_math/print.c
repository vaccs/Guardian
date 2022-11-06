
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

static const char* lookup[] = {
	[imek_add] = "+",
	[imek_subtract] = "-",
	[imek_multiply] = "*",
};

void int_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	struct int_math_expression* this = (void*) super;
	
	expression_print(this->left);
	
	assert(lookup[this->kind]);
	
	printf(" %s ", lookup[this->kind]);
	
	expression_print(this->right);
	
	EXIT;
}

























