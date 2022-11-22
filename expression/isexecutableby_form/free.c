
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_isexecutableby_form_expression(
	struct expression* super)
{
	struct isexecutableby_form_expression* const this = (void*) super;
	ENTER;
	
	free_expression(this->user);
	
	free_expression(this->path);
	
	EXIT;
}

