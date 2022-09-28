
#include <debug.h>

#include <parse/parse.h>

#include "struct.h"
#include "new.h"

struct named_zebu_expression* new_named_zebu_expression(
	struct string* name,
	struct zebu_expression* expression)
{
	ENTER;
	
	struct named_zebu_expression* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->expression = inc_zebu_expression(expression);
	
	EXIT;
	return this;
}


