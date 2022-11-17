
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include <list/expression/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* funccall_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct funccall_expression* this = (void*) super;
	
	expression_print(this->lambda);
	
	printf("(");
	
	struct expression_list* arguments = this->arguments;
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		expression_print(arguments->data[i]);
		
		if (i + 1 < n)
			printf(", ");
	}
	
	printf(")");
	#endif
	
	EXIT;
}

























