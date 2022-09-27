
#include <debug.h>

#include <string/inc.h>

#include <type/inc.h>

#include "struct.h"
#include "new.h"

struct parameter* new_parameter(
	struct string* name,
	struct type* type)
{
	ENTER;
	
	struct parameter* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->type = inc_type(type);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

