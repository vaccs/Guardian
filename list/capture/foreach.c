
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void capture_list_foreach(
	struct capture_list* this,
	void (*runme)(
		struct capture* capture))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
	
	EXIT;
}

