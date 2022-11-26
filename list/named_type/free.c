
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <named/type/free.h>

#include "struct.h"
#include "free.h"

void free_named_type_list(
	struct named_type_list* this)
{
	if (this && !--this->refcount)
	{
		for (unsigned i = 0, n = this->n; i < n; i++)
			free_named_type(this->data[i]);
		
		free(this->data);
		free(this);
	}
}

