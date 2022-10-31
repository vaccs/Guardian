
#include <debug.h>

#include "node/struct.h"

#include "struct.h"
#include "encase.h"

void unresolved_encase(
	struct unresolved* this)
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct unresolved_node* ele = node->item;
		ptrset_update(ele->layers.deeper, ele->layers.current);
		ptrset_clear(ele->layers.current);
	}
	
	EXIT;
}

