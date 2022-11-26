
#include <debug.h>

/*#include <type_cache/get_type/float.h>*/

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_float_value(
	struct type* type,
	long double value)
{
	ENTER;
	
	struct float_value* this = (void*) new_value(
		type,
		vk_float,
		&float_value_inheritance,
		sizeof(*this));
	
	this->value = value;
	
	EXIT;
	return (void*) this;
}

