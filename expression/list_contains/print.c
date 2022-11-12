
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <expression/print.h>

#include "struct.h"
#include "print.h"

void list_contains_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_list_contains);
	
	struct list_contains_expression* this = (void*) super;
	
	expression_print(this->element);
	
	printf(" in ");
	
	expression_print(this->list);
	
	EXIT;
}

