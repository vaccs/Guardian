
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

/*#include <avl/free_tree.h>*/

#include "struct.h"
#include "free.h"

void free_stateinfo(struct stateinfo* this)
{
	ENTER;
	
	TODO;
	#if 0
	if (this && !--this->refcount)
	{
		avl_free_tree(this->tree);
		free(this);
	}
	#endif
	
	EXIT;
}

