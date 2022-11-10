
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <type/dict/struct.h>
#include <type/dict/new.h>

#include "../struct.h"

#include "dict.h"

struct type* type_cache_get_dict_type(
	struct type_cache* this,
	struct type* key,
	struct type* value)
{
	struct type* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct dict_type){
		.super.kind = tk_dict,
		.key = key,
		.value = value,
	});
	
	if (node)
	{
		retval = node->item;
	}
	else
	{
		struct type* dict = new_dict_type(this->next++, key, value);
		
		avl_insert(this->tree, dict);
		
		retval = dict;
	}
	
	EXIT;
	return retval;
}
