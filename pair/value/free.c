
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <value/free.h>

#include "struct.h"
#include "free.h"

void free_value_pair(
	void* ptr)
{
	ENTER;
	
	struct value_pair* this = ptr;
	
	if (this && !--this->refcount)
	{
		free_value(this->key);
		free_value(this->value);
		
		free(this);
	}
	
	EXIT;
}

