
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_assertion(
	struct assertion* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		free_expression(this->expression);
		
		free(this);
	}
	
	EXIT;
}

