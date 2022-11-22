
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_isdir_form_expression(
	struct expression* super)
{
	struct isdir_form_expression* const this = (void*) super;
	ENTER;
	
	free_expression(this->path);
	
	EXIT;
}

