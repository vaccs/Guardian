
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <type/tuple/struct.h>
#include <type/tuple/new.h>

#include "../struct.h"

#include "tuple.h"

struct type* type_cache_get_tuple_type(
	struct type_cache* this,
	struct type_list* subtypes)
{
	struct type* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct tuple_type){
		.super.kind = tk_tuple,
		.subtypes = subtypes,
	});
	
	if (node)
	{
		retval = node->item;
	}
	else
	{
		struct type* tuple = new_tuple_type(this->next++, subtypes);
		
		avl_insert(this->tree, tuple);
		
		retval = tuple;
	}
	
	EXIT;
	return retval;
}
