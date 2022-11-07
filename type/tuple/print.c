
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <list/type/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void tuple_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_tuple);
	
	struct tuple_type* this = (void*) super;
	
	printf("(");
	
	unsigned i, n;
	
	for (i = 0, n = this->subtypes->n; i < n; i++)
	{
		type_print(this->subtypes->data[i]);
		
		if (i + 1 < n)
			printf(", ");
	}
	
	if (n == 1)
	{
		printf(", ");
	}
	
	printf(")");
	
	EXIT;
}







