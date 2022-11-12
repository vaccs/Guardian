
#include <debug.h>

#include <list/value_pair/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_dict_value(
	struct type* type,
	struct value_pair_list* elements)
{
	ENTER;
	
	struct dict_value* this = (void*) new_value(
		type,
		vk_dict,
		&dict_value_inheritance,
		sizeof(*this));
	
	this->elements = inc_value_pair_list(elements);
	
	EXIT;
	return (void*) this;
}



