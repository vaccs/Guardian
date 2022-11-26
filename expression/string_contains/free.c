
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_string_contains_expression(
	struct expression* super)
{
	struct string_contains_expression* const this = (void*) super;
	ENTER;
	
	free_expression(this->substring);
	
	free_expression(this->string);
	
	EXIT;
}

