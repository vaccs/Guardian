
#include <debug.h>

#include <set/zpexpression/update.h>

#include "node/struct.h"
#include "node/inc.h"

#include "struct.h"
#include "update.h"

void unresolved_update(
	struct unresolved* a,
	const struct unresolved* b)
{
	ENTER;
	
	struct avl_node_t* an = a->tree->head;
	struct avl_node_t* bn = b->tree->head;
	
	while (an && bn)
	{
		struct unresolved_node *ae = an->item, *be = bn->item;
		
		int cmp = compare_strings(ae->name, be->name);
		
		if (cmp < 0)
		{
			TODO;
		}
		else if (cmp > 0)
		{
			TODO;
		}
		else
		{
			zpexpressionset_update(ae->layers.current, be->layers.current);
			zpexpressionset_update(ae->layers.deeper, be->layers.deeper);
			
			an = an->next, bn = bn->next;
		}
	}
	
	while (bn)
	{
		struct unresolved_node* be = bn->item;
		
		avl_insert(a->tree, inc_unresolved_node(be));
		
		a->n++;
		
		bn = bn->next;
	}
	
	EXIT;
}














