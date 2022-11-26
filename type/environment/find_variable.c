
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <named/type/struct.h>

#include "struct.h"
#include "find_variable.h"

unsigned environment_type_find_variable(
	struct type* super,
	struct string* name,
	struct type* type)
{
	unsigned depth = 0;
	ENTER;
	
	assert(super->kind == tk_environment);
	
	struct environment_type* moving = (void*) super;
	
	while (moving)
	{
		dpv(moving);
		
		#ifdef DEBUGGING
		{
			for (struct avl_node_t* node = moving->variables->head; node; node = node->prev)
			{
				struct named_type* ntype = node->item;
				
				dpvs(ntype->name);
			}
		}
		#endif
		
		struct avl_node_t* node = avl_search(moving->variables, &name);
		
		if (node)
		{
			struct named_type* ntype = node->item;
			
			assert(ntype->type == type);
			break;
		}
		else
		{
			moving = (void*) moving->prev, depth++;
		}
	}
	
	assert(moving);
	
	EXIT;
	return depth;
}








