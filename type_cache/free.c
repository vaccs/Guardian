
#include <debug.h>

#include <type/free.h>

#include "struct.h"
#include "free.h"

void free_type_cache(struct type_cache* this)
{
	ENTER;
	
	avl_free_tree(this->tree);
	
	free_type(this->int_type);
	free_type(this->bool_type);
	
	free(this);
	
	EXIT;
}

