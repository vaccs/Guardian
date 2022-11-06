
#include <stdlib.h>

#include <debug.h>

#include <assertion/free.h>

#include "struct.h"
#include "free.h"

void free_assertion_list(
	struct assertion_list* this)
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		free_assertion(this->data[i]);
	}
	
	free(this->data);
	
	free(this);
	
	EXIT;
}

