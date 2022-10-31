
#include <debug.h>

#include "node/struct.h"
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
			ptrset_update(ae->layers.current, be->layers.current);
			ptrset_update(ae->layers.deeper, be->layers.deeper);
			
			an = an->next, bn = bn->next;
		}
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














