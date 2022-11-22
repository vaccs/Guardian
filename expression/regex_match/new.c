
#include <debug.h>

#include <expression/struct.h>
#include <expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_regex_match_expression(
	struct type* type,
	struct expression* expression,
	struct regex* regex)
{
	ENTER;
	
	struct regex_match_expression* this = (void*) new_expression(
		ek_regex_match,
		&regex_match_expression_inheritance,
		type,
		sizeof(*this));
	
	this->expression = inc_expression(expression);
	
	this->regex = regex;
	
	EXIT;
	return (void*) this;
}

