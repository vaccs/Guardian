
#include <debug.h>

#include <list/parameter/free.h>

#include <expression/free.h>

#include <scope/free.h>

#include "struct.h"
#include "free.h"

void free_lambda_value(
	struct value* super)
{
	ENTER;
	
	struct lambda_value* this = (void*) super;
	
	free_scope(this->captured);
	
	free_parameter_list(this->parameters);
	
	free_expression(this->body);
	
	EXIT;
}

