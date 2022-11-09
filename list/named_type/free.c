
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_named_type_list(
	struct named_type_list* this)
{
	if (this && !--this->refcount)
	{
		TODO;
		
		free(this->data);
		free(this);
	}
}

