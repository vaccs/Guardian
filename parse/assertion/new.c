
#include <debug.h>

#include "../parse.h"

#include "struct.h"
#include "new.h"

struct raw_assertion* new_raw_assertion(
	enum assertion_kind kind,
	struct zebu_expression* expression)
{
	ENTER;
	
	struct raw_assertion* this = smalloc(sizeof(*this));
	
	this->kind = kind;
	
	this->expression = inc_zebu_expression(expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}


