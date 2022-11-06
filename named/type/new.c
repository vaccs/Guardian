
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include "struct.h"
#include "new.h"

struct named_type* new_named_type(
	struct string* name,
	struct type* type)
{
	ENTER;
	
	struct named_type* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	this->type = type;
	
	EXIT;
	return this;
}

