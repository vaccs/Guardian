
#include <debug.h>

#include <memory/smalloc.h>

#include <value/inc.h>

#include "struct.h"
#include "new.h"

struct value_pair* new_value_pair(
	struct value* key,
	struct value* value)
{
	ENTER;
	
	struct value_pair* this = smalloc(sizeof(*this));
	
	this->key = inc_value(key);
	this->value = inc_value(value);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

