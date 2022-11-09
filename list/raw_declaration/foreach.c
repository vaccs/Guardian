
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void raw_declaration_list_foreach(
	struct raw_declaration_list* this,
	void (*runme)(struct raw_declaration* this))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(this->data[i]);
	}
	
	EXIT;
}

