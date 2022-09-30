
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_parenthesis_expression(
	struct expression* super)
{
	struct parenthesis_expression* const this = (void*) super;
	ENTER;
	
	free_expression(this->expression);
	
	EXIT;
}

