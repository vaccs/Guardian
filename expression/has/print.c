
#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void has_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_has);
	
	struct has_expression* this = (void*) super;
	
	printf("has(");
	
	expression_print(this->list);
	
	printf(")");
	#endif
	
	EXIT;
}

