
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_fieldaccess_expression(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct fieldaccess_expression* this = (void*) super;
	
	free_expression(this->list);
	#endif
	
	EXIT;
}

