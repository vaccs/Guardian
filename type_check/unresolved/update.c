
#include <debug.h>

#include "node/inc.h"

#include "struct.h"
#include "update.h"

void unresolved_update(
	struct unresolved* this,
	const struct unresolved* other)
{
	ENTER;
	
	struct avl_node_t* an = this->tree->head;
	struct avl_node_t* bn = other->tree->head;
	
	while (an && bn)
	{
		TODO;
	}
	
	while (bn)
	{
		struct unresolved_node* be = bn->item;
		
		avl_insert(this->tree, inc_unresolved_node(be));
		
		this->n++;
		
		bn = bn->next;
	}
	
	EXIT;
}














