
#include <stdlib.h>

#include <debug.h>

#include <statement/free.h>

#include "struct.h"
#include "free.h"

void free_statement_list(
	struct statement_list* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		while (this->n--)
			free_statement(this->data[this->n]);
		
		free(this->data);
		free(this);
	}
	
	EXIT;
}

