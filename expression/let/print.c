
#include <assert.h>

#include <stdio.h>

#include <debug.h>

#include <string/struct.h>

/*#include <list/parameter/struct.h>*/

/*#include <parameter/struct.h>*/

/*#include <type/print.h>*/

#include <named/expression/struct.h>

#include <list/named_expression/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* let_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_let);
	
	struct let_expression* this = (void*) super;
	
	printf("let! ");
	
	struct named_expression_list* parameters = this->parameters;
	
	for (unsigned i = 0, n = parameters->n; i < n; i++)
	{
		struct named_expression* ele = parameters->data[i];
		
		printf("%.*s = ", ele->name->len, ele->name->chars);
		
		expression_print(ele->expression);
		
		if (i + 1 < n)
			printf(", ");
	}
	
	printf(": ");
	
	expression_print(this->body);
	#endif
	
	EXIT;
}

























