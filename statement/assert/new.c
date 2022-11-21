
#include <debug.h>

#include <expression/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct statement* new_assert_statement(
	unsigned line,
	enum assertion_kind kind,
	struct expression* expression)
{
	ENTER;
	
	struct assert_statement* this = (void*) new_statement(
		sk_assert,
		&assert_statement_inheritance,
		sizeof(*this));
	
	this->line = line;
	
	this->kind = kind;
	
	this->expression = inc_expression(expression);
	
	EXIT;
	return (void*) this;
}
