
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_set_contains_expression(
	struct type* type,
	struct expression* element,
	struct expression* set)
{
	ENTER;
	
	struct set_contains_expression* this = (void*) new_expression(
		ek_set_contains,
		&set_contains_expression_inheritance,
		type,
		sizeof(*this));
	
	this->element = inc_expression(element);
	
	this->set = inc_expression(set);
	
	EXIT;
	return (void*) this;
}

