
#include <debug.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct type_lookup* new_type_lookup(
	struct quack* all_types)
{
	ENTER;
	
	struct type_lookup* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_type_lookup_nodes, free_type_lookup_node);
	
	this->next = 0;
	
	EXIT;
	return this;
}


