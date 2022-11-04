
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct value* new_value(
	struct type* type,
	enum value_kind kind,
	struct value_inheritance* inheritance,
	size_t alloc_size)
{
	ENTER;
	
	dpv(alloc_size);
	
	struct value* this = smalloc(alloc_size);
	
	this->type = type;
	
	this->kind = kind;
	
	this->inheritance = inheritance;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}
