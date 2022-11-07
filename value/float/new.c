
#include <debug.h>

#include <type_cache/get_type/float.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_float_value(
	struct type_cache* tcache,
	long double value)
{
	ENTER;
	
	struct float_value* this = (void*) new_value(
		type_cache_get_float_type(tcache),
		vk_float,
		&float_value_inheritance,
		sizeof(*this));
	
	this->value = value;
	
	EXIT;
	return (void*) this;
}

