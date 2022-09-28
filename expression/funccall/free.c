
#include <debug.h>

#include <expression/free.h>

#include <list/expression/free.h>

#include "struct.h"
#include "free.h"

void free_funccall_expression(
	struct expression* super)
{
	ENTER;
	
	struct funccall_expression* this = (void*) super;
	
	free_expression(this->lambda);
	
	free_expression_list(this->arguments);
	
	EXIT;
}

