
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void statement_list_foreach(
	struct statement_list* this,
	void (*runme)(struct statement*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(this->data[i]);
	}
	
	EXIT;
}

