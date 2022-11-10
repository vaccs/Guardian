
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void dict_index_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_dict_index);
	
	struct dict_index_expression* this = (void*) super;
	
	expression_print(this->list);
	
	printf("[");
	
	expression_print(this->index);
	
	printf("]");
	#endif
	
	EXIT;
}

