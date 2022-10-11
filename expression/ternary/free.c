
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_ternary_expression(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct ternary_expression* this = (void*) super;
	
	free_expression(this->list);
	#endif
	
	EXIT;
}

