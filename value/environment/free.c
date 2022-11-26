
#include <debug.h>

#include <avl/free_tree.h>

#include "../free.h"

#include "struct.h"

#include "free.h"

void free_environment_value(
	struct value* super)
{
	ENTER;
	
	struct environment_value* this = (void*) super;
	
	avl_free_tree(this->variables);
	
	free_value(this->prev);
	
	EXIT;
}

