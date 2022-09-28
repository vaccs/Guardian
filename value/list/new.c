
#include <debug.h>

#include <list/value/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_list_value(
	struct type* type,
	struct value_list* elements)
{
	ENTER;
	
	struct list_value* this = (void*) new_value(
		type,
		vk_list,
		&list_value_inheritance,
		sizeof(*this));
	
	this->elements = inc_value_list(elements);
	
	EXIT;
	return (void*) this;
}

