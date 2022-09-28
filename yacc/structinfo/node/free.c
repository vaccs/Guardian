
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_structinfo_node(void* ptr)
{
	ENTER;
	
	struct structinfo_node* node = ptr;
	
	if (node && !--node->refcount)
	{
		free_string(node->name);
		
		free_string(node->grammar);
	
		free(node);
	}
	
	EXIT;
}

