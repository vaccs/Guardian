
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void expression_pair_list_foreach(
	struct expression_pair_list* this,
	void (*runme)(struct expression_pair*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(this->data[i]);
	}
	
	EXIT;
}

