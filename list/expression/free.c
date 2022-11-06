
#include <stdlib.h>

#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_expression_list(
	struct expression_list* this)
{
	if (this && !--this->refcount)
	{
		while (this->n--)
			free_expression(this->data[this->n]);
		
		free(this->data);
		free(this);
	}
}

