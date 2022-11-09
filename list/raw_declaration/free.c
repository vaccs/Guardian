
#include <stdlib.h>

#include <debug.h>

#include <parse/declaration/free.h>

#include "struct.h"
#include "free.h"

void free_raw_declaration_list(
	struct raw_declaration_list* this)
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		free_raw_declaration(this->data[i]);
	}
	
	free(this->data);
	free(this);
	
	EXIT;
}

