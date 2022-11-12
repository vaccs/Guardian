
#include <debug.h>

/*#include <set/expression/free.h>*/

#include "struct.h"
#include "free.h"

void free_set_expression(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct set_expression* this = (void*) super;
	
	free_expression_set(this->elements);
	#endif
	
	EXIT;
}

