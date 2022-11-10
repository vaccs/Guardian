
#include <assert.h>

#include <debug.h>

/*#include <list/parameter/free.h>*/

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_let_expression(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct let_expression* this = (void*) super;
	
	free_parameter_list(this->parameters);
	
	free_expression(this->body);
	#endif
	
	EXIT;
}

