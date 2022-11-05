
#include <debug.h>

#include <avl/clear_tree.h>

#include "struct.h"
#include "clear.h"

void zpexpressionset_clear(
	struct zpexpressionset* this)
{
	ENTER;
	
	avl_clear_tree(this->tree);
	
	EXIT;
}

