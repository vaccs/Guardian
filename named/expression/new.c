
#include <debug.h>

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
	
	EXIT;
	return this;
}

