
#include <debug.h>

#include <avl/search.h>
#include <avl/delete_node.h>

#include "struct.h"
#include "discard.h"

void value_to_id_discard(
	struct value_to_id* this,
	struct value* super)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &super);
	
	assert(node);
	
	avl_delete_node(this->tree, node);
	
	EXIT;
}

