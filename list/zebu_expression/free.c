
#include <debug.h>

#include <parse/parse.h>

#include "struct.h"
#include "free.h"

void free_zebu_expression_list(
	struct zebu_expression_list* this)
{
	if (this && !--this->refcount)
	{
		while (this->n--)
			free_zebu_expression(this->data[this->n]);
		
		free(this->data);
		free(this);
	}
}

