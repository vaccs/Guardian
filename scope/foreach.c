
#include <debug.h>

#include <named/value/struct.h>

#include "struct.h"
#include "foreach.h"

void scope_foreach(
	const struct scope* this,
	void (*runme)(struct string* name, struct value* value))
{
	ENTER;
	
	assert(this);
	assert(this->tree);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct named_value* ele = node->item;
		
		runme(ele->name, ele->value);
	}
	
	EXIT;
}

