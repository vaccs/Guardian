
#include <stdio.h>

#include <debug.h>

#include <string/struct.h>

#include <list/parameter/struct.h>

#include <parameter/struct.h>

#include <type/print.h>

#include <expression/print.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void lambda_value_print(
	struct value* super)
{
	ENTER;
	
	struct lambda_value* spef = (void*) super;
	
	printf("$");
	
	struct parameter_list* parameters = spef->parameters;
	
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
	
	expression_print(spef->body);
	
	EXIT;
}

