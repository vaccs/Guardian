
#include <debug.h>

#include <value/free.h>

#include "struct.h"
#include "free.h"

void free_literal_expression(
	struct expression* super)
{
	struct literal_expression* const this = (void*) super;
	ENTER;
	
	free_value(this->value);
	
	EXIT;
}

