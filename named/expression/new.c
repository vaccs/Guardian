
#include <debug.h>

#include <string/inc.h>

#include <memory/smalloc.h>

#include <expression/inc.h>

#include "struct.h"
#include "new.h"

struct named_expression* new_named_expression(
	struct string* name,
	struct expression* expression)
{
	ENTER;
	
	struct named_expression* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->expression = inc_expression(expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

