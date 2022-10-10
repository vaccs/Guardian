
#include <debug.h>

#include "struct.h"
#include "new.h"

void free_function_lookup(
	struct function_lookup* this)
{
	ENTER;
	
	avl_free_tree(this->tree);
	
	free(this);
	
	EXIT;
}

