
#include <debug.h>

#include <list/type/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_lambda_type(
	struct type* super)
{
	ENTER;
	
	struct lambda_type* this = (void*) super;
	
	free_type_list(this->parameters);
	
	EXIT;
}

