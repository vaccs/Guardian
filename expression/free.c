
#include <debug.h>

#include <type/free.h>

#include "inheritance.h"
#include "struct.h"
#include "free.h"

void free_expression(
	struct expression* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		assert(this->inheritance->free);
		
		(this->inheritance->free)(this);
		
		free(this);
	}
	
	EXIT;
}

