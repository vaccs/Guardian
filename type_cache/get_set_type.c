
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <type/set/struct.h>
#include <type/set/new.h>

#include "struct.h"

#include "get_set_type.h"

struct type* type_cache_get_set_type(
	struct type_cache* this,
	struct type* element_type)
{
	struct type* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct set_type){
		.super.kind = tk_set,
		.element_type = element_type
	});
	
	if (node)
	{
		retval = node->item;
	}
	else
	{
		struct type* set = new_set_type(this->next++, element_type);
		
		avl_insert(this->tree, set);
		
		retval = set;
	}
	
	EXIT;
	return retval;
}
