
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_float_expression(
	struct expression* super)
{
	ENTER;
	
	struct float_expression* this = (void*) super;
	
	free_expression(this->subexpression);
	
	EXIT;
}

