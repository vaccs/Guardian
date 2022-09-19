
#include <debug.h>

#include "struct.h"
#include "new.h"

struct type* new_type(
	enum type_kind kind,
	unsigned size)
{
	ENTER;
	
	struct type* this = smalloc(size);
	
	this->kind = kind;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}


