
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_bool_not_expression(
	struct expression* super)
{
	struct bool_not_expression* const this = (void*) super;
	ENTER;
	
	free_expression(this->subexpression);
	
	EXIT;
}

