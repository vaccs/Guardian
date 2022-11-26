
#include <debug.h>

#include <list/named_type/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_lambda_expression(
	struct expression* super)
{
	ENTER;
	
	struct lambda_expression* this = (void*) super;
	
	free_named_type_list(this->parameters);
	
	free_expression(this->body);
	
	EXIT;
}

