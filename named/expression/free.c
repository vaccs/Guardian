
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_named_expression(void* ptr)
{
	ENTER;
	
	struct named_expression* this = ptr;
	
	dpvs(this->name);
	
	free_string(this->name);
	
	free_expression(this->expression);
	
	free(this);
	
	EXIT;
}

