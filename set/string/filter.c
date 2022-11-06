
#include <stdbool.h>

#include <debug.h>

#include <avl/delete_node.h>
#include <avl/tree.h>

#include "struct.h"
#include "filter.h"

void stringset_filter(
	struct stringset* this,
	bool (*filter)(struct string*))
{
	ENTER;
	
	struct avl_node_t* head = this->tree->head;
	
	struct avl_node_t* next;
	
	while (head)
	{
		next = head->next;
		
		bool keep = filter(head->item);
		
		if (!keep)
		{
			#ifdef DEBUGGING
			struct string* removing = head->item;
			dpvs(removing);
			#endif
			
			avl_delete_node(this->tree, head);
			this->n--;
		}
		
		head = next;
	}
	
	EXIT;
}














