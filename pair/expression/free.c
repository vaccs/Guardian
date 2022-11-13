
#include <stdlib.h>

#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_expression_pair(
	struct expression_pair* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		free_expression(this->key);
		free_expression(this->value);
		
		free(this);
	}
	
	EXIT;
}

