
#include <debug.h>

#include "struct.h"
#include "clear.h"

void ptrset_clear(
	struct ptrset* this)
{
	ENTER;
	
	avl_clear_tree(this->tree);
	
	EXIT;
}

