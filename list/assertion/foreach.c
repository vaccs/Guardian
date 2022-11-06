
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void assertion_list_foreach(
	struct assertion_list* this,
	void (*runme)(struct assertion* this))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(this->data[i]);
	}
	
	EXIT;
}

