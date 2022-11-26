
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_string_value(
	struct type* type,
	unsigned char* chars,
	unsigned len)
{
	ENTER;
	
	struct string_value* this = (void*) new_value(
		type,
		vk_string,
		&string_value_inheritance,
		sizeof(*this));
	
	this->chars = chars;
	this->len = len;
	
	EXIT;
	return (void*) this;
}

