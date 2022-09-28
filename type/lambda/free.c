
#include <debug.h>

#include <list/parameter/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_lambda_type(
	struct type* super)
{
	ENTER;
	
	struct lambda_type* this = (void*) super;
	
	free_parameter_list(this->parameters);
	
	free_type(this->rettype);
	
	EXIT;
}

