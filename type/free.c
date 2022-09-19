
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_type(void* ptr)
{
	struct type* this = ptr;
	
	if (this && !--this->refcount)
	{
		TODO;
	}
}

