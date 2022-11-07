
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void expression_list_foreach(
	struct expression_list* this,
	void (*runme)(struct expression*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(this->data[i]);
	}
	
	EXIT;
}

