
#include <debug.h>

#include "node/compare.h"
#include "node/inc.h"

#include "struct.h"
#include "update.h"

void structinfo_update(
	struct structinfo* this,
	const struct structinfo* other)
{
	ENTER;
	
	struct avl_node_t* an = this->tree->head, *bn = other->tree->head;
	
	while (an && bn)
	{
		struct structinfo_node *ae = an->item, *be = bn->item;
		
		int cmp = compare_structinfo_nodes(ae, be);
		
		if (cmp < 0)
		{
			TODO;
		}
		else if (cmp > 0)
		{
			avl_insert(this->tree, inc_structinfo_node(be));
			bn = bn->next;
		}
		else
		{
			TODO;
		}
	}
	
	while (bn)
	{
		struct structinfo_node* be = bn->item;
		avl_insert(this->tree, inc_structinfo_node(be));
		bn = bn->next;
	}
	
	EXIT;
}










