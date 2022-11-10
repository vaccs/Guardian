
#include <stdlib.h>

#include <debug.h>

#include <pair/expression/free.h>

#include "struct.h"
#include "free.h"

void free_expression_pair_list(
	struct expression_pair_list* this)
{
	if (this && !--this->refcount)
	{
		while (this->n--)
			free_expression_pair(this->data[this->n]);
		
		free(this->data);
		free(this);
	}
}

