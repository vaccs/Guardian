
#include <debug.h>

#include <type/inc.h>

#include "struct.h"
#include "new.h"

struct expression* new_expression(
	enum expression_kind kind,
	struct expression_inheritance* inheritance,
	struct type* type,
	size_t alloc_size)
{
	ENTER;
	
	struct expression* this = smalloc(alloc_size);
	
	this->kind = kind;
	
	this->inheritance = inheritance;
	
	this->type = inc_type(type);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

