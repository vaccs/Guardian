
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <type/list/struct.h>
#include <type/list/new.h>

#include "../struct.h"

#include "list.h"

struct type* type_cache_get_list_type(
	struct type_cache* this,
	struct type* element_type)
{
	struct type* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct list_type){
		.super.kind = tk_list,
		.element_type = element_type
	});
	
	if (node)
	{
		retval = node->item;
	}
	else
	{
		struct type* list = new_list_type(this->next++, element_type);
		
		avl_insert(this->tree, list);
		
		retval = list;
	}
	
	EXIT;
	return retval;
}
