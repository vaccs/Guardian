
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* ternary_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_ternary);
	
	struct ternary_expression* this = (void*) super;
	
	expression_print(this->conditional);
	
	printf(" ? ");
	
	expression_print(this->true_case);
	
	printf(" : ");
	
	expression_print(this->false_case);
	#endif
	
	EXIT;
}

