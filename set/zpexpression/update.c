
#include <assert.h>

#include <debug.h>

#include <avl/tree.h>
#include <avl/insert.h>

#include <parse/parse.h>

#include "struct.h"
#include "update.h"

void zpexpressionset_update(
	struct zpexpressionset* a,
	const struct zpexpressionset* b)
{
	ENTER;
	
	assert(a != b);
	
	struct avl_node_t *an = a->tree->head, *bn = b->tree->head;
	
	while (an && bn)
	{
		struct zebu_primary_expression *ae = an->item, *be = bn->item;
		
		if (ae < be)
		{
			an = an->next;
		}
		else if (ae > be)
		{
			avl_insert(a->tree, inc_zebu_primary_expression(be));
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
		avl_insert(a->tree, inc_zebu_primary_expression(bn->item));
		bn = bn->next;
	}
	
	EXIT;
}

