
#include <debug.h>

#include "node/struct.h"
#include "struct.h"
#include "foreach.h"

void unresolved_foreach(
	const struct unresolved* this,
	void (*runme)(struct string* name))
{
	ENTER;
	
	struct avl_node_t* current, *next = NULL;
	
	current = this->tree->head;
	
	if (current && current->next)
		next = current->next;
	
	while (current)
	{
		struct unresolved_node* node = current->item;
		
		runme(node->name);
		
		current = next;
		
		if (current && current->next)
			next = current->next;
	}
	
	EXIT;
}











