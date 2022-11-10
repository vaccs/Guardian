
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

/*#include <value/compare.h>*/

#include <pair/value/new.h>

/*#include <list/value_pair/struct.h>*/

#include "struct.h"
#include "set.h"

void dict_value_set(
	struct value* super,
	struct value* key,
	struct value* value)
{
	ENTER;
	
	assert(super->kind == vk_dict);
	
	struct dict_value* this = (void*) super;
	
	struct avl_node_t* node = avl_search(this->tree, &key);
	
	if (node)
	{
		TODO;
	}
	else
	{
		struct value_pair* pair = new_value_pair(key, value);
		
		void* ptr = avl_insert(this->tree, pair);
		
		assert(ptr);
	}
	
	EXIT;
}











