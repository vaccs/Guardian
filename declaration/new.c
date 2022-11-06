
#include <debug.h>

#include <expression/inc.h>

#include "struct.h"
#include "new.h"

struct declaration* new_declaration(
	struct string* name,
	struct expression* expression)
{
	ENTER;
	
	struct declaration* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->expression = inc_expression(expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

