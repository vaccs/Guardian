
#include <stdlib.h>

#include <debug.h>

#include <expression/free.h>

#include <string/free.h>

#include "struct.h"
#include "free.h"

void free_declaration(
	struct declaration* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		free_string(this->name);
		
		free_expression(this->expression);
		
		free(this);
	}
	
	EXIT;
}

