
#include <debug.h>

#include <expression/struct.h>
#include <expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_parenthesis_expression(
	struct expression* expression)
{
	ENTER;
	
	struct parenthesis_expression* this = (void*) new_expression(
		ek_parenthesis,
		&parenthesis_expression_inheritance,
		expression->type,
		sizeof(*this));
	
	this->expression = inc_expression(expression);
	
	EXIT;
	return (void*) this;
}

