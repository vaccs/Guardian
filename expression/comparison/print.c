
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* comparison_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_comparison);
	
	struct comparison_expression* this = (void*) super;
	
	expression_print(this->left);
	
	if (!lookup[this->kind])
	{
		TODO;
	}
	
	printf(" %s ", lookup[this->kind]);
	
	expression_print(this->right);
	#endif
	
	EXIT;
}


