
#include <stdlib.h>
#include <debug.h>

#include <avl/alloc_tree.h>

#include <memory/smalloc.h>

#include "new.h"
#include "struct.h"

static int compare_nodes(const void* a, const void* b)
{
	const struct value_to_id_node *A = a, *B = b;
	
	if (A->value > B->value)
		return +1;
	else if (A->value < B->value)
		return -1;
	else
		return +0;
}

struct value_to_id* new_value_to_id()
{
	ENTER;
	
	struct value_to_id* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_nodes, free);
	
	this->next_id = 1;
	
	EXIT;
	return this;
}

