
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

static const char* lookup[] = {
	[cek_equal_to] = "==",
	[cek_less_than] = "<",
	[cek_not_equal_to] = "!=",
};

void comparison_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_comparison);
	
	struct comparison_expression* this = (void*) super;
	
	expression_print(this->left);
	
	if (!lookup[this->kind])
	{
		TODO;
	}
	
	printf(" %s ", lookup[this->kind]);
	
	expression_print(this->right);
	
	EXIT;
}


