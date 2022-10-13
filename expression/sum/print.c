
#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void sum_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_sum);
	
	struct sum_expression* this = (void*) super;
	
	printf("sum(");
	
	expression_print(this->list);
	
	printf(")");
	
	EXIT;
}

