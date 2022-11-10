
#include <debug.h>

#include <memory/smalloc.h>

#include <value/inc.h>

#include "struct.h"
#include "new.h"

struct value_pair* new_value_pair(
	struct value* first,
	struct value* second)
{
	ENTER;
	
	struct value_pair* this = smalloc(sizeof(*this));
	
	this->first = inc_value(first);
	this->second = inc_value(second);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

