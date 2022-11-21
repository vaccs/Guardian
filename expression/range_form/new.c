
#include <debug.h>

#include <expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_range_form_expression(
	struct type* type,
	struct expression* start,
	struct expression* end)
{
	ENTER;
	
	struct range_form_expression* this = (void*) new_expression(
		ek_range_form,
		&range_form_expression_inheritance,
		type,
		sizeof(*this));
	
	this->start = inc_expression(start);
	
	this->end = inc_expression(end);
	
	EXIT;
	return (void*) this;
}

