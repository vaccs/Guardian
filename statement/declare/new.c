
#include <debug.h>

#include <string/inc.h>

#include <expression/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct statement* new_declare_statement(
    unsigned line,
	struct string* name,
	struct expression* expression)
{
	ENTER;
	
	struct declare_statement* this = (void*) new_statement(
	    line,
		sk_declare,
		&declare_statement_inheritance,
		sizeof(*this));
	
	this->name = inc_string(name);
	
	this->expression = inc_expression(expression);
	
	EXIT;
	return (void*) this;
}

