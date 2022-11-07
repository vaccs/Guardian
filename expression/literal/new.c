
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_literal_expression(struct value* value)
{
	ENTER;
	
	assert(value);
	assert(value->type);
	
	struct literal_expression* this = (void*) new_expression(
		ek_literal,
		&literal_expression_inheritance,
		value->type,
		sizeof(*this));
	
	this->value = inc_value(value);
	
	EXIT;
	return (void*) this;
}

