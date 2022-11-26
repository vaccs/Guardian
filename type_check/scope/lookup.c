
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

/*#include <type_cache/get_type/list.h>*/

/*#include <named/type/struct.h>*/

#include <value/inc.h>

#include "node/struct.h"

#include "layer.h"
#include "struct.h"
#include "lookup.h"

bool type_check_scope_lookup_type(
	struct type_check_scope* this,
	struct string* name,
	struct type** out_type)
{
	bool found = false;
	ENTER;
	
	for (struct type_check_scope_layer* current = this->head;
		!found && current; current = current->prev)
	{
		struct avl_node_t* node = avl_search(current->tree, &name);
		
		if (node)
		{
			struct type_check_scope_node* entry = node->item;
			
			if (!entry->type)
			{
				TODO;
			}
			
			*out_type = entry->type;
			found = true;
		}
	}
	
	EXIT;
	return found;
}


bool type_check_scope_lookup(
	struct type_check_scope* this,
	struct string* name,
	struct type** out_type,
	struct value** out_value)
{
	bool found = false;
	ENTER;
	
	void helper(struct type_check_scope_layer* layer)
	{
		ENTER;
		
		if (layer)
		{
			struct avl_node_t* node = avl_search(layer->tree, &name);
			
			if (node)
			{
				struct type_check_scope_node* entry = node->item;
				
				assert(entry->type);
				
				*out_type = entry->type;
				*out_value = inc_value(entry->value);
				
				found = true;
			}
			else if (helper(layer->prev), found && !*out_value)
			{
				layer->is_pure = false;
			}
		}
		
		EXIT;
	}
	
	helper(this->head);
	
	EXIT;
	return found;
}















