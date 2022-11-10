
#include <assert.h>

#include <debug.h>

/*#include <dict/expression/free.h>*/

#include "struct.h"
#include "free.h"

void free_dict_expression(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct dict_expression* this = (void*) super;
	
	free_expression_dict(this->elements);
	#endif
	
	EXIT;
}

