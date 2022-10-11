
#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void ternary_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_ternary);
	
	struct ternary_expression* this = (void*) super;
	
	printf("ternary(");
	
	expression_print(this->list);
	
	printf(")");
	#endif
	
	EXIT;
}

