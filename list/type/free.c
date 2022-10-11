
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_type_list(
	struct type_list* this)
{
	if (this && !--this->refcount)
	{
		free(this->data);
		free(this);
	}
}

