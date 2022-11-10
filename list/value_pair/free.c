
#include <stdlib.h>

#include <debug.h>

#include <pair/value/free.h>

#include "struct.h"
#include "free.h"

void free_value_pair_list(
	struct value_pair_list* this)
{
	if (this && !--this->refcount)
	{
		while (this->n--)
			free_value_pair(this->data[this->n]);
		
		free(this->data);
		free(this);
	}
}

