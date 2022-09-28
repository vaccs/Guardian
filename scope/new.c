
#include <debug.h>

#include <named/value/compare.h>
#include <named/value/free.h>

#include "struct.h"
#include "new.h"

struct scope* new_scope()
{
	ENTER;
	
	struct scope* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_named_values, free_named_value);
	
	EXIT;
	return this;
}

