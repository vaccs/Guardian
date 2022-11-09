
#include <assert.h>

#include <debug.h>

#include <string/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_variable_expression(
	struct type* type,
	struct string* name)
{
	ENTER;
	
	assert(type);
	
	struct variable_expression* this = (void*) new_expression(
		ek_variable,
		&variable_expression_inheritance,
		type,
		sizeof(struct variable_expression));
	
	this->name = inc_string(name);
	
	EXIT;
	return (void*) this;
}

