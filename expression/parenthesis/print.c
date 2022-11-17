
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <expression/print.h>

#include "struct.h"
#include "print.h"

struct stringtree* parenthesis_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_parenthesis);
	
	struct parenthesis_expression* this = (void*) super;
	
	printf("(");
	
	expression_print(this->expression);
	
	printf(")");
	#endif
	
	EXIT;
}

