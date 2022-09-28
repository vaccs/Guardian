
#include <debug.h>

#include <named/value/new.h>

#include "struct.h"
#include "declare.h"

void scope_declare(
	struct scope* this,
	struct string* name,
	struct value* value)
{
	ENTER;
	
	struct avl_node_t* node = avl_insert(this->tree, new_named_value(name, value));
	
	assert(node);
	
	EXIT;
}

