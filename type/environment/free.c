
#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_environment_type(
	struct type* super)
{
	ENTER;
	
	struct environment_type* this = (void*) super;
	
	avl_free_tree(this->variables);
	
	EXIT;
}

