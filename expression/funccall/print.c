
#include <debug.h>

#include <list/expression/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void funccall_expression_print(
	struct expression* super)
{
	ENTER;
	
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
	
	EXIT;
}

























