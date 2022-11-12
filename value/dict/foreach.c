
#if 0
#include <debug.h>

#include <avl/tree.h>

#include <pair/value/struct.h>

#include "struct.h"
#include "foreach.h"

void dict_value_foreach(
	struct dict_value* this,
	void (*runme)(
		struct value* key,
		struct value* value))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct value_pair* pair = node->item;
		
		runme(pair->first, pair->second);
	}
	
	EXIT;
}

#endif
