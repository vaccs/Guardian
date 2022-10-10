
#include <debug.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct function_lookup* new_function_lookup()
{
	ENTER;
	
	struct function_lookup* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_function_lookup_nodes, free_function_lookup_node);
	
	this->next = 0;
	
	EXIT;
	return this;
}

