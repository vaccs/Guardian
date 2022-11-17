
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void raw_statement_list_foreach(
	struct raw_statement_list* this,
	void (*runme)(struct raw_statement*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(this->data[i]);
	}
	
	EXIT;
}

