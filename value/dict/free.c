
#include <assert.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_dict_value(
	struct value* super)
{
	ENTER;
	
	struct dict_value* this = (void*) super;
	
	avl_free_tree(this->tree);
	
	EXIT;
}

