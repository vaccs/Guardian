
#include <debug.h>

#include <expression/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct statement* new_print_statement(
	struct expression* expression)
{
	ENTER;
	
	struct print_statement* this = (void*) new_statement(
		sk_print,
		&print_statement_inheritance,
		sizeof(*this));
	
	this->expression = inc_expression(expression);
	
	EXIT;
	return (void*) this;
}
