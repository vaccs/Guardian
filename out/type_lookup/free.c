
#include <debug.h>

#include "struct.h"
#include "new.h"

void free_type_lookup(
	struct type_lookup* this)
{
	ENTER;
	
	avl_free_tree(this->tree);
	
	free(this);
	
	EXIT;
}


