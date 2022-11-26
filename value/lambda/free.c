
#include <debug.h>

#include <list/named_type/free.h>

#include <expression/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_lambda_value(
	struct value* super)
{
	ENTER;
	
	struct lambda_value* this = (void*) super;
	
	free_value(this->captured);
	
	free_named_type_list(this->parameters);
	
	free_expression(this->body);
	
	EXIT;
}

