
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* sum_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_sum_form);
	
	struct sum_expression* this = (void*) super;
	
	printf("sum!(");
	
	expression_print(this->list);
	
	printf(")");
	#endif
	
	EXIT;
}

