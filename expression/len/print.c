
#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void len_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_len);
	
	struct len_expression* this = (void*) super;
	
	printf("len(");
	
	expression_print(this->list);
	
	printf(")");
	
	EXIT;
}

