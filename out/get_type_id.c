
#include <debug.h>

#include "shared.h"
#include "type_to_id_node.h"
#include "get_type_id.h"

unsigned out_get_type_id(
	struct out_shared* shared,
	struct type* type)
{
	unsigned retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(shared->type.lookup, &type);
	
	if (node)
	{
		struct type_to_id_node* old = node->item;
		
		retval = old->id;
	}
	else
	{
		struct type_to_id_node* new = smalloc(sizeof(*new));
		
		new->type = type;
		new->id = retval = shared->type.next++;
		
		avl_insert(shared->type.lookup, new);
	}
	
	EXIT;
	return retval;
}

