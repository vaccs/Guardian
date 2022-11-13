
#include <stdlib.h>

#include <debug.h>

#include <value/free.h>

#include "struct.h"
#include "free.h"

void free_value_list(
	struct value_list* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		while (this->n--)
		{
			free_value(this->data[this->n]);
		}
		
		free(this->data);
		free(this);
	}
	
	EXIT;
}

