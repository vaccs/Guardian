
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_structinfo_node(void* ptr)
{
	ENTER;
	
	struct structinfo_node* node = ptr;
	
	if (node && !--node->refcount)
	{
		TODO;
	}
	
	EXIT;
}

