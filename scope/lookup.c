
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
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &name);
	
	if (!node)
	{
		TODO;
		exit(1);
	}
	
	struct named_value* nvalue = node->item;
	
	EXIT;
	return inc_value(nvalue->value);
}

