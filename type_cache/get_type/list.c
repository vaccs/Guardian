
#include <debug.h>

#include <type/list/struct.h>
#include <type/list/new.h>
#include <type/inc.h>

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
		retval = inc_type(node->item);
	}
	else
	{
		struct type* list = new_list_type(element_type);
		
		avl_insert(this->tree, list);
		
		retval = inc_type(list);
	}
	
	EXIT;
	return retval;
}
