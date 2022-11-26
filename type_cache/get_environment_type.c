
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <type/environment/struct.h>
#include <type/environment/new.h>

#include "struct.h"

#include "get_environment_type.h"

struct type* type_cache_get_environment_type2(
	struct type_cache* this,
	struct type* prev,
	struct avl_tree_t* variables) // named types
{
	struct environment_type* retval;
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
		struct environment_type* environment = new_environment_type(
			this->next++, prev, variables);
		
		void* ptr = avl_insert(this->tree, environment);
		
		assert(ptr);
		
		retval = environment;
	}
	
	EXIT;
	return (void*) retval;
}
















