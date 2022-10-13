
#include <debug.h>

#include <list/type/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void lambda_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_lambda);
	
	struct lambda_type* this = (void*) super;
	
	printf("$");
	
	for (unsigned i = 0, n = this->parameters->n; i < n; i++)
	{
		type_print(this->parameters->data[i]);
		
		if (i + 1 < n)
			printf(", ");
	}
	
	printf(":");
	
	type_print(this->rettype);
	
	EXIT;
}

