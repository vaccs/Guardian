
#include <debug.h>

#include <type/compare.h>
#include <type/free.h>

#include "struct.h"
#include "new.h"

struct type_cache* new_type_cache()
{
	ENTER;
	
	struct type_cache* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_types, free_type);
	
	EXIT;
	return this;
}

