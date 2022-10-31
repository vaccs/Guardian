
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_unresolved_node(void* ptr)
{
	ENTER;
	
	struct unresolved_node* this = ptr;
	
	if (this && !--this->refcount)
	{
		free_string(this->name);
		free_ptrset(this->layers.current);
		free_ptrset(this->layers.deeper);
		free(this);
	}
	
	EXIT;
}

