
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_fieldaccess_expression(
	struct expression* super)
{
	ENTER;
	
	struct fieldaccess_expression* this = (void*) super;
	
	free_expression(this->object);
	
	free_string(this->fieldname);
	
	EXIT;
}

