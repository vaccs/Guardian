
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void named_expression_list_foreach(
	struct named_expression_list* this,
	void (*runme)(struct named_expression*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
	
	EXIT;
}

