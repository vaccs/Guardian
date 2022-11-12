
#include <debug.h>

#include <list/value/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_set_value(
	struct type* type,
	struct value_list* elements)
{
	ENTER;
	
	struct set_value* this = (void*) new_value(
		type,
		vk_set,
		&set_value_inheritance,
		sizeof(*this));
	
	this->elements = inc_value_list(elements);
	
	EXIT;
	return (void*) this;
}

