
#include <stddef.h>

#include <debug.h>

#include <string/inc.h>

#include <expression/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct statement* new_parse_statement(
	unsigned line,
	struct expression* expression,
	struct string* grammar_name,
	struct gegex* grammar)
{
	ENTER;
	
	struct parse_statement* this = (void*) new_statement(
	    line,
		sk_parse,
		&parse_statement_inheritance,
		sizeof(*this));
	
	this->expression = inc_expression(expression);
	
	this->grammar_name = inc_string(grammar_name);
	
	this->grammar = grammar;
	
	this->ystate = NULL;
	
	EXIT;
	return (void*) this;
}
