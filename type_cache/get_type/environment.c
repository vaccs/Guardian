
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <type/environment/struct.h>
#include <type/environment/new.h>

#include "../struct.h"

#include "environment.h"

struct type* type_cache_get_environment_type(
	struct type_cache* this,
	struct type* prev,
	struct avl_tree_t* variables)
{
	struct type* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct environment_type){
		.super.kind = tk_environment,
		.prev = prev,
		.variables = variables,
	});
	
	if (node)
	{
		retval = node->item;
	}
	else
	{
		struct type* environment = new_environment_type(
			this->next++, prev, variables);
		
		avl_insert(this->tree, environment);
		
		retval = environment;
	}
	
	EXIT;
	return retval;
}
