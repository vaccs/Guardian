
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void string_list_foreach(
	struct string_list* this,
	void (*runme)(struct string*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(this->data[i]);
	}
	
	EXIT;
}

