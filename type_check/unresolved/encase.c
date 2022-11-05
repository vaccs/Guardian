
#include <debug.h>

#include <avl/tree.h>

#include <set/zpexpression/update.h>
#include <set/zpexpression/clear.h>

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
		zpexpressionset_update(ele->layers.deeper, ele->layers.current);
		zpexpressionset_clear(ele->layers.current);
	}
	
	EXIT;
}

