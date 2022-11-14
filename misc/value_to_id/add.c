
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "struct.h"
#include "add.h"

bool value_to_id_add(
	struct value_to_id* this,
	unsigned *out_id,
	struct value* value)
{
	ENTER;
	
	bool new;
	
	struct avl_node_t* node = avl_search(this->tree, &value);
	
	if (node)
	{
		struct value_to_id_node* old = node->item;
		*out_id = old->id;
		new = false;
	}
	else
	{
		struct value_to_id_node* node = smalloc(sizeof(*node));
		
		node->value = value;
		node->id = *out_id = this->next_id++;
		
		void* ptr = avl_insert(this->tree, node);
		assert(ptr);
		
		new = true;
	}
	
	EXIT;
	return new;
}

