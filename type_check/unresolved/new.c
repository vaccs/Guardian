
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct unresolved* new_unresolved()
{
	ENTER;
	
	struct unresolved* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_unresolved_nodes, free_unresolved_node);
	
	this->refcount = 1;
	
	this->n = 0;
	
	EXIT;
	return this;
}

