
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <named/value/struct.h>

#include <value/inc.h>

#include "struct.h"
#include "lookup.h"

struct value* scope_lookup(
	struct scope* this,
	struct string* name)
{
	struct value* retval = NULL;
	ENTER;
	
	dpvs(name);
	
	for (struct scope* moving = this; moving; moving = moving->prev)
	{
		dpv(moving);
		
		struct avl_node_t* node = avl_search(moving->tree, &name);
		
		if (node)
		{
			struct named_value* nvalue = node->item;
			
			retval = inc_value(nvalue->value);
		}
	}
	
	if (!retval)
	{
		TODO;
		exit(1);
	}
	
	EXIT;
	return retval;
}

