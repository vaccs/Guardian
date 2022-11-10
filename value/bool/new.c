
#include <debug.h>

#include <type_cache/get_type/bool.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_bool_value(
	struct type* type,
	bool value)
{
	ENTER;
	
	struct bool_value* this = (void*) new_value(
		type,
		vk_bool,
		&bool_value_inheritance,
		sizeof(*this));
	
	this->value = value;
	
	EXIT;
	return (void*) this;
}

