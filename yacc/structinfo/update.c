
#include <debug.h>

#include "struct.h"
#include "update.h"

void structinfo_update(
	struct structinfo* this,
	const struct structinfo* other)
{
	ENTER;
	
	struct avl_node_t* an = this->tree->head, *bn = other->tree->head;
	
	while (an && bn)
	{
		TODO;
	}
	
	while (bn)
	{
		TODO;
	}
	
	EXIT;
}

