
#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "foreach.h"

void zpexpressionset_foreach(
	const struct zpexpressionset* this,
	void (*runme)(struct zebu_primary_expression* zpexpression))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		runme(node->item);
	}
	
	EXIT;
}

