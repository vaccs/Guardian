
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void declaration_list_foreach(
	struct declaration_list* this,
	void (*runme)(struct declaration* this))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(this->data[i]);
	}
	
	EXIT;
}

