
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void list_index_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_list_index);
	
	struct list_index_expression* this = (void*) super;
	
	expression_print(this->list);
	
	printf("[");
	
	expression_print(this->index);
	
	printf("]");
	
	EXIT;
}

