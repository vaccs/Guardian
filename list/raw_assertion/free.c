
#include <debug.h>

#include <parse/assertion/free.h>

#include "struct.h"
#include "free.h"

void free_raw_assertion_list(
	struct raw_assertion_list* this)
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		free_raw_assertion(this->data[i]);
	}
	
	free(this->data);
	free(this);
	
	EXIT;
}

