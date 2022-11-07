
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_tuple_index_expression(
	struct expression* super)
{
	ENTER;
	
	struct tuple_index_expression* this = (void*) super;
	
	free_expression(this->tuple);
	
	EXIT;
}

