
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <list/expression/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void map_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_map);
	
	struct map_expression* this = (void*) super;
	
	printf("map(");
	
	expression_print(this->lambda);
	
	for (unsigned i = 0, n = this->arguments->n; i < n; i++)
	{
		printf(", ");
		
		expression_print(this->arguments->data[i]);
	}
	
	printf(")");
	
	EXIT;
}

