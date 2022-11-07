
#include <assert.h>

#include <stdio.h>

#include <debug.h>

/*#include <string/struct.h>*/

/*#include <list/parameter/struct.h>*/

/*#include <parameter/struct.h>*/

/*#include <type/print.h>*/

#include <list/expression/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void tuple_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_tuple);
	
	struct tuple_expression* this = (void*) super;
	
	printf("(");
	
	unsigned i, n;
	
	for (i = 0, n = this->subexpressions->n; i < n; i++)
	{
		expression_print(this->subexpressions->data[i]);
		
		if (i + 1 < n)
			printf(", ");
	}
	
	if (n == 1)
		printf(", ");
	
	printf(")");
	
	EXIT;
}

























