
#include <debug.h>

#include "tree.h"
#include "inc.h"

struct avl_tree_t* inc_avltree(
	struct avl_tree_t* this)
{
	if (this)
		this->refcount++;
	return this;
}


