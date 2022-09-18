
#include <debug.h>

#include "new.h"

struct value* new_integer_value(int64_t value)
{
	struct type* type = new_integer_type();
	
	struct value* super = new_value(
		sizeof(struct integer_value));
	
	struct integer_value* this = super;
	
	this->value = value;
	
	TODO;
}

