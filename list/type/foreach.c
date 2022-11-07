
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void type_list_foreach(
	struct type_list* this,
	void (*runme)(struct type*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
	
	EXIT;
}

