
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <named/value/struct.h>

#include <value/inc.h>

#include "struct.h"
#include "assign.h"

void environment_value_assign(
	struct value* super,
	struct string* name,
	struct value* value)
{
	ENTER;
	
	assert(super->kind == vk_environment);
	
	struct environment_value* this = (void*) super;
	
	struct avl_node_t* node = avl_search(this->variables, &name);
	
	assert(node);
	
	struct named_value* nvalue = node->item;
	
	assert(!nvalue->value);
	
	nvalue->value = inc_value(value);
	
	EXIT;
}

