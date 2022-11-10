
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_named_expression(void* ptr)
{
	ENTER;
	
	struct named_expression* this = ptr;
	
	if (this && !--this->refcount)
	{
		dpvs(this->name);
		
		free_string(this->name);
		
		free_expression(this->expression);
		
		free(this);
	}
	
	EXIT;
}

