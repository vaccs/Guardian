
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_capture(
	struct capture* this)
{
	if (this && !--this->refcount)
	{
		TODO;
	}
}

