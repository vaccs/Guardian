
#include <assert.h>

#include <debug.h>

#include <avl/tree.h>
#include <avl/insert.h>

#include "struct.h"
#include "update.h"

void ptrset_update(
	struct ptrset* this,
	const struct ptrset* them)
{
	ENTER;
	
	struct avl_node_t* an = this->tree->head;
	struct avl_node_t* bn = them->tree->head;
	
	while (an && bn)
	{
		void *ae = an->item, *be = bn->item;
		
		if (ae < be)
		{
			an = an->next;
		}
		else if (ae > be)
		{
			avl_insert(this->tree, be);
			bn = bn->next;
		}
		else
		{
			TODO;
		}
	}
	
	while (bn)
	{
		avl_insert(this->tree, bn->item);
		bn = bn->next;
	}
	
	EXIT;
}

