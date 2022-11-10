
#include <debug.h>

#include <avl/search.h>
#include <avl/delete_node.h>

#include "struct.h"
#include "discard.h"

void unresolved_discard(
	struct unresolved* this,
	struct string* name)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &name);
	
	if (node)
	{
		avl_delete_node(this->tree, node);
		
		this->n--;
	}
	
	EXIT;
}

