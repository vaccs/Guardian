
#include <debug.h>

#include "layer.h"
#include "struct.h"
#include "lookup.h"

bool type_check_scope_lookup(
	struct type_check_scope* this,
	struct string* name,
	struct type** out_type,
	struct value** out_value)
{
	bool found = false;
	ENTER;
	
	for (struct type_check_scope_layer* current = this->head;
		!found && current; current = current->prev)
	{
		TODO;
	}
	
	// if a type (without a value) was found at any layer, all layers
	// between are no longer pure
	TODO;
	
	if (!found)
	{
		TODO;
	}
	
	if (!found)
	{
		TODO;
	}
	
	EXIT;
	return found;
}


