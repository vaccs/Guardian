
#include <stddef.h>
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <pair/value/struct.h>

#include <value/inc.h>

#include "struct.h"
#include "lookup.h"

struct value* dict_value_lookup(
	struct value* super,
	struct value* key)
{
	ENTER;
	
	assert(super->kind == vk_dict);
	
	struct dict_value* this = (void*) super;
	
	struct avl_node_t* node = avl_search(this->tree, &key);
	
	struct value* value = NULL;
	
	if (node)
	{
		struct value_pair* pair = node->item;
		
		value = inc_value(pair->second);
	}
	
	EXIT;
	return value;
}

