
#include <debug.h>

#include <avl/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct environment_type* new_environment_type(
	unsigned id,
	struct environment_type* prev,
	struct avl_tree_t* variables)
{
	ENTER;
	
	struct environment_type* this = (void*) new_type(
		id,
		tk_environment,
		&environment_type_inheritance,
		sizeof(*this));
	
	this->prev = prev;
	
	this->variables = inc_avltree(variables);
	
	EXIT;
	return this;
}

