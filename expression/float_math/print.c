
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

static const char* lookup[] = {
	[fmek_add] = "+",
	[fmek_subtract] = "-",
	[fmek_multiply] = "*",
};

void float_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	struct float_math_expression* this = (void*) super;
	
	expression_print(this->left);
	
	assert(lookup[this->kind]);
	
	printf(" %s ", lookup[this->kind]);
	
	expression_print(this->right);
	
	EXIT;
}

























