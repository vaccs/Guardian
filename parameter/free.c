
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_parameter(
	struct parameter* this)
{
	if (this && !--this->refcount)
	{
		TODO;
	}
}

