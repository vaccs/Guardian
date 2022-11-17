
#include <stdlib.h>

#include <debug.h>

#include <parse/raw_statement/free.h>

#include "struct.h"
#include "free.h"

void free_raw_statement_list(
	struct raw_statement_list* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		while (this->n--)
			free_raw_statement(this->data[this->n]);
		
		free(this->data);
		free(this);
	}
	
	EXIT;
}

