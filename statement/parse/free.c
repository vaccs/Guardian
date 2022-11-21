
#include <debug.h>

#include <string/free.h>

#include <expression/free.h>

#include <yacc/state/free.h>

#include "struct.h"
#include "free.h"

void free_parse_statement(
	struct statement* super)
{
	ENTER;
	
	struct parse_statement* this = (void*) super;
	
	free_string(this->grammar_name);
	
	free_expression(this->expression);
	
	// free_yacc_state(this->ystate);
	
	EXIT;
}

