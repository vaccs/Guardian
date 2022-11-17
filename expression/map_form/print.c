
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <list/expression/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* map_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_map_form);
	
	struct map_form_expression* this = (void*) super;
	
	printf("map!(");
	
	expression_print(this->lambda);
	
	for (unsigned i = 0, n = this->arguments->n; i < n; i++)
	{
		printf(", ");
		
		expression_print(this->arguments->data[i]);
	}
	
	printf(")");
	#endif
	
	EXIT;
}

