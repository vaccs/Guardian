
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_variable_expression(
	struct expression* super)
{
	ENTER;
	
	struct variable_expression* this = (void*) super;
	
	free_string(this->name);
	
	EXIT;
}

