
#include <debug.h>

#include <avl/alloc_tree.h>

#include <named/value/compare.h>
#include <named/value/free.h>

#include <value/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_environment_value(
	struct type* type,
	struct value* prev)
{
	ENTER;
	
	struct environment_value* this = (void*) new_value(
		type,
		vk_environment,
		&environment_value_inheritance,
		sizeof(*this));
	
	this->variables = avl_alloc_tree(compare_named_values, free_named_value);
	
	this->prev = inc_value(prev);
	
	EXIT;
	return (void*) this;
}

