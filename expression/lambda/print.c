
#include <debug.h>

#include <list/parameter/struct.h>

#include <parameter/struct.h>

#include <type/print.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void lambda_expression_print(
	struct expression* super)
{
	ENTER;
	
	struct lambda_expression* this = (void*) super;
	
	printf("$");
	
	struct parameter_list* parameters = this->parameters;
	
	for (unsigned i = 0, n = parameters->n; i < n; i++)
	{
		struct parameter* ele = parameters->data[i];
		
		if (ele->type)
		{
			type_print(ele->type);
			printf(" ");
		}
		
		printf("%.*s", ele->name->len, ele->name->chars);
		
		if (i + 1 < n)
			printf(", ");
	}
	
	printf(": ");
	
	expression_print(this->body);
	
	EXIT;
}

























