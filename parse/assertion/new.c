
#include <debug.h>

#include "../parser.h"

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
	
	EXIT;
	return this;
}


