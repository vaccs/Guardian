
#include <debug.h>

#include <type/free.h>

#include "inheritance.h"
#include "struct.h"
#include "free.h"

void free_value(struct value* this)
{
	if (this && !--this->refcount)
	{
		assert(this->inheritance->free);
		
		(this->inheritance->free)(this);
		
		free(this);
	}
}

