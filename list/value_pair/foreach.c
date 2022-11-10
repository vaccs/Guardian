
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void value_pair_list_foreach(
	struct value_pair_list* this,
	void (*runme)(struct value_pair*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(this->data[i]);
	}
	
	EXIT;
}

