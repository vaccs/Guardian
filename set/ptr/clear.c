
#include <debug.h>

#include <avl/clear_tree.h>

#include "struct.h"
#include "clear.h"

void ptrset_clear(
	struct ptrset* this)
{
	ENTER;
	
	avl_clear_tree(this->tree);
	
	EXIT;
}

