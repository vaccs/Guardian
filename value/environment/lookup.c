
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <avl/search.h>

#include <named/value/struct.h>

#include <value/inc.h>

#include <defines/argv0.h>

#include "struct.h"
#include "lookup.h"

struct value* environment_value_lookup(
	struct value* super,
	struct string* name)
{
	struct value* retval = NULL;
	ENTER;
	
	dpvs(name);
	
	assert(super->kind == vk_environment);
	
	for (struct environment_value* moving = (void*) super; !retval && moving;)
	{
		dpv(moving);
		
		struct avl_node_t* node = avl_search(moving->variables, &name);
		
		if (node)
		{
			struct named_value* nvalue = node->item;
			
			retval = inc_value(nvalue->value);
		}
		else if (moving->prev)
		{
			assert(moving->prev->kind == vk_environment);
			
			moving = (void*) moving->prev;
		}
		else
		{
			fprintf(stderr, "%s: use of undefined variable '%.*s'!\n",
				argv0, name->len, name->chars);
			exit(1);
		}
	}
	
	EXIT;
	return retval;
}











