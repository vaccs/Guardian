
#include <debug.h>

#include "struct.h"
#include "new.h"

struct type* new_type(
	unsigned id,
	enum type_kind kind,
	struct type_inheritance* inheritance,
	unsigned size)
{
	ENTER;
	
	dpv(inheritance);
	
	struct type* this = smalloc(size);
	
	this->id = id;
	
	this->kind = kind;
	
	this->inheritance = inheritance;
	
	EXIT;
	return this;
}


