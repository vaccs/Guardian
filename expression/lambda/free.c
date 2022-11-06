
#include <debug.h>

#include <list/parameter/free.h>

#include <list/capture/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_lambda_expression(
	struct expression* super)
{
	ENTER;
	
	struct lambda_expression* this = (void*) super;
	
	free_parameter_list(this->parameters);
	
	free_capture_list(this->captured);
	
	free_expression(this->body);
	
	EXIT;
}

