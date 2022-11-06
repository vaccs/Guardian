
#include <stdlib.h>

#include <debug.h>

#include <capture/free.h>

#include "struct.h"
#include "free.h"

void free_capture_list(
	struct capture_list* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		for (unsigned i = 0, n = this->n; i < n; i++)
			free_capture(this->data[i]);
		
		free(this->data);
		free(this);
	}
	
	EXIT;
}

