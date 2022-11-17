
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <expression/print.h>

#include "struct.h"
#include "print.h"

struct stringtree* dict_contains_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_dict_contains);
	
	struct dict_contains_expression* this = (void*) super;
	
	expression_print(this->index), printf(" in "), expression_print(this->dict);
	#endif
	
	EXIT;
}

