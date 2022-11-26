
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_string_contains_expression(
	struct type* type,
	struct expression* substring,
	struct expression* string)
{
	ENTER;
	
	struct string_contains_expression* this = (void*) new_expression(
		ek_string_contains,
		&string_contains_expression_inheritance,
		type,
		sizeof(*this));
	
	this->substring = inc_expression(substring);
	
	this->string = inc_expression(string);
	
	EXIT;
	return (void*) this;
}

