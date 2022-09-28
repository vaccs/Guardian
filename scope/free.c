
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_scope(struct scope* this)
{
	if (this)
	{
		avl_free_tree(this->tree);
		free(this);
	}
}

