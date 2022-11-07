
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void float_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_float);
	
	struct float_expression* this = (void*) super;
	
	printf("float(");
	
	expression_print(this->list);
	
	printf(")");
	#endif
	
	EXIT;
}

