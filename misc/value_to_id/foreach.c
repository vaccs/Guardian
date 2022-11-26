
#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "foreach.h"

void value_to_id_foreach(
	struct value_to_id* this,
	void (*runme)(unsigned, struct value*))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct value_to_id_node* item = node->item;
		
		runme(item->id, item->value);
	}
	
	EXIT;
}

