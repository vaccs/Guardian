
#include <debug.h>

#include <string/free.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_declare_statement(
	struct statement* super)
{
	ENTER;
	
	struct declare_statement* this = (void*) super;
	
	free_string(this->name);
	
	free_expression(this->expression);
	
	EXIT;
}

