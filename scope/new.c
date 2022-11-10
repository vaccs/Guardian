
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include <named/value/compare.h>
#include <named/value/free.h>

#include "struct.h"
#include "inc.h"
#include "new.h"

struct scope* new_scope(
	struct scope* prev)
{
	ENTER;
	
	struct scope* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_named_values, free_named_value);
	
	this->prev = inc_scope(prev);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

