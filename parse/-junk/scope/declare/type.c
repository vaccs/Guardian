
#include <debug.h>

#include <named/type/new.h>

#include "../struct.h"
#include "type.h"

void scope_declare_type(
	struct scope* this,
	struct string* name,
	struct type* type)
{
	ENTER;
	
	struct named_type* ntype = new_named_type(name, type);
	
	struct avl_node_t* node = avl_insert(this->named_types, ntype);
	
	if (!node)
	{
		TODO;
	}
	
	EXIT;
}

