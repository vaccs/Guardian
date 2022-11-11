
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <named/value/struct.h>

#include <value/inc.h>

#include "struct.h"
#include "assign.h"

void scope_assign(
	struct scope* this,
	struct string* name,
	struct value* value)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &name);
	
	assert(node);
	
	struct named_value* nvalue = node->item;
	
	assert(!nvalue->value);
	
	nvalue->value = inc_value(value);
	
	EXIT;
}

