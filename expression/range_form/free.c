
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_range_form_expression(
	struct expression* super)
{
	struct range_form_expression* const this = (void*) super;
	ENTER;
	
	free_expression(this->start);
	
	free_expression(this->end);
	
	EXIT;
}

