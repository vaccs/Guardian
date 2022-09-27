
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_value_list(
	struct value_list* this)
{
	if (this && !--this->refcount)
	{
		TODO;
	}
}

