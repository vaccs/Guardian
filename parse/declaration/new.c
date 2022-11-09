
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include <parse/parse.h>

#include "struct.h"
#include "new.h"

struct raw_declaration* new_raw_declaration(
	struct string* name,
	struct zebu_expression* expression)
{
	ENTER;
	
	struct raw_declaration* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->expression = inc_zebu_expression(expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}




