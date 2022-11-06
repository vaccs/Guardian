
#include <debug.h>

#include <memory/smalloc.h>

#include <expression/inc.h>

#include "struct.h"
#include "new.h"

struct assertion* new_assertion(
	enum assertion_kind kind,
	struct expression* expression)
{
	ENTER;
	
	struct assertion* this = smalloc(sizeof(*this));
	
	this->kind = kind;
	
	this->expression = inc_expression(expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

