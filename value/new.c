
#include <debug.h>

#include <type/inc.h>

#include "struct.h"
#include "new.h"

struct value* new_value(
	struct type* type,
	struct value_inheritance* inheritance,
	size_t alloc_size)
{
	ENTER;
	
	dpv(alloc_size);
	
	struct value* this = smalloc(alloc_size);
	
	this->type = inc_type(type);
	
	this->inheritance = inheritance;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}
