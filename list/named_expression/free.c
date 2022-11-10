
#include <stdlib.h>

#include <debug.h>

#include <named/expression/free.h>

#include "struct.h"
#include "free.h"

void free_named_expression_list(
	struct named_expression_list* this)
{
	if (this && !--this->refcount)
	{
		for (unsigned i = 0, n = this->n; i < n; i++)
			free_named_expression(this->data[i]);
		
		free(this->data);
		free(this);
	}
}

