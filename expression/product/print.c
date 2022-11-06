
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void product_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_product);
	
	struct product_expression* this = (void*) super;
	
	printf("product(");
	
	expression_print(this->list);
	
	printf(")");
	
	EXIT;
}

