
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_value_pair(
	void* ptr)
{
	ENTER;
	
	struct value_pair* this = ptr;
	
	if (this && !--this->refcount)
	{
		TODO;
	}
	
	EXIT;
}

