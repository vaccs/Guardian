
#include <debug.h>

#include <parse/parse.h>

#include "struct.h"
#include "update.h"

void zpexpressionset_update(
	struct zpexpressionset* a,
	const struct zpexpressionset* b)
{
	ENTER;
	
	struct avl_node_t* an = a->tree->head;
	struct avl_node_t* bn = b->tree->head;
	
	while (an && bn)
	{
		struct zebu_primary_expression *ae = an->item, *be = bn->item;
		
		if (ae < be)
		{
			an = an->next;
		}
		else if (ae > be)
		{
			avl_insert(a->tree, be);
			inc_zebu_primary_expression(be);
			bn = bn->next;
		}
		else
		{
			an = an->next;
			bn = bn->next;
		}
	}
	
	while (bn)
	{
		avl_insert(a->tree, bn->item);
		inc_zebu_primary_expression(bn->item);
		bn = bn->next;
	}
	
	EXIT;
}

