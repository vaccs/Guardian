
#include <debug.h>

#include <expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_bool_not_expression(
	struct type* type,
	struct expression* subexpression)
{
	ENTER;
	
	struct bool_not_expression* this = (void*) new_expression(
		ek_bool_not,
		&bool_not_expression_inheritance,
		type,
		sizeof(*this));
	
	this->subexpression = inc_expression(subexpression);
	
	EXIT;
	return (void*) this;
}

