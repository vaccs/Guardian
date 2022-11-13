
#include <assert.h>

#include <debug.h>

#include <avl/tree.h>

#include <named/value/struct.h>

#include "struct.h"
#include "foreach.h"

void scope_foreach(
	const struct scope* this,
	void (*runme)(struct string* name, struct value* value))
{
	ENTER;
	
	if (this)
	{
		assert(this->tree);
	
		for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		{
			struct named_value* ele = node->item;
			
			runme(ele->name, ele->value);
		}
	}
	
	EXIT;
}

void scope_foreach_layer(
	struct scope* this,
	void (*runme)(struct scope*))
{
	ENTER;
	
	if (this)
	{
		scope_foreach_layer(this->prev, runme);
		
		runme(this);
	}
	
	EXIT;
}






















