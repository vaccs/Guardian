
#include <debug.h>

#include <avl/alloc_tree.h>

#include <memory/smalloc.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct structinfo* new_structinfo()
{
	ENTER;
	
	struct structinfo* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_structinfo_nodes, free_structinfo_node);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

