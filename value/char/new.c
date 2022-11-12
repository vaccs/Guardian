
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_char_value(
	struct type* type,
	unsigned char value)
{
	ENTER;
	
	struct char_value* this = (void*) new_value(
		type,
		vk_char,
		&char_value_inheritance,
		sizeof(*this));
	
	this->value = value;
	
	EXIT;
	return (void*) this;
}

