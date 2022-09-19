
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_structinfo(struct structinfo* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		avl_free_tree(this->tree);
		free(this);
	}
	
	EXIT;
}

