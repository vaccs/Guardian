
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* all_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_all_form);
	
	struct all_form_expression* this = (void*) super;
	
	printf("len!(");
	
	expression_print(this->object);
	
	printf(")");
	#endif
	
	EXIT;
}

