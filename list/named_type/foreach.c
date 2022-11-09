
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void named_type_list_foreach(
	struct named_type_list* this,
	void (*runme)(struct named_type*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
	
	EXIT;
}

