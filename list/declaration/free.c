
#include <debug.h>

#include <declaration/free.h>

#include "struct.h"
#include "free.h"

void free_declaration_list(
	struct declaration_list* this)
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		free_declaration(this->data[i]);
	}
	
	free(this->data);
	free(this);
	
	EXIT;
}

