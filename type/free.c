
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "free.h"

void free_type(void* ptr)
{
	ENTER;
	
	struct type* this = ptr;
	
	if (this && !--this->refcount)
	{
		assert(this->inheritance);
		assert(this->inheritance->free);
		
		(this->inheritance->free)(this);
		
		free(this);
	}
	
	EXIT;
}

