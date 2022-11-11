
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <named/type/struct.h>

#include "struct.h"
#include "find_variable.h"

unsigned environment_type_find_variable(
	struct environment_type* this,
	struct string* name,
	struct type* type)
{
	unsigned depth = 0;
	ENTER;
	
	struct environment_type* moving = this;
	
	while (moving)
	{
		struct avl_node_t* node = avl_search(this->variables, &name);
		
		if (node)
		{
			struct named_type* ntype = node->item;
			
			assert(ntype->type == type);
			break;
		}
		else
		{
			moving = moving->prev, depth++;
		}
	}
	
	assert(moving);
	
	EXIT;
	return depth;
}

