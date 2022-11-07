
#include <assert.h>

#include <stdio.h>

#include <debug.h>

/*#include <string/struct.h>*/

/*#include <list/parameter/struct.h>*/

/*#include <parameter/struct.h>*/

/*#include <type/print.h>*/

/*#include <expression/print.h>*/

#include <list/value/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void tuple_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_tuple);
	
	struct tuple_value* this = (void*) super;
	
	printf("(");
	
	unsigned i, n;
	
	for (i = 0, n = this->subvalues->n; i < n; i++)
	{
		value_print(this->subvalues->data[i]);
		
		if (i + 1 < n)
			printf(", ");
	}
	
	if (n == 1)
		printf(", ");
	
	printf(")");
	
	EXIT;
}















