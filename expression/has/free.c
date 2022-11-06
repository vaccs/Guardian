
#include <assert.h>

#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_has_expression(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct has_expression* this = (void*) super;
	
	free_expression(this->list);
	#endif
	
	EXIT;
}

