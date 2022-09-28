
#include <debug.h>

#include <list/expression/free.h>

#include "struct.h"
#include "free.h"

void free_list_expression(
	struct expression* super)
{
	ENTER;
	
	struct list_expression* this = (void*) super;
	
	free_expression_list(this->elements);
	
	EXIT;
}

