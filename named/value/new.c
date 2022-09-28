
#include <debug.h>

#include <value/inc.h>

#include "struct.h"
#include "new.h"

struct named_value* new_named_value(
	struct string* name,
	struct value* value)
{
	ENTER;
	
	struct named_value* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	this->value = inc_value(value);
	
	EXIT;
	return this;
}

