
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_assert_statement(
	struct statement* super)
{
	ENTER;
	
	struct assert_statement* this = (void*) super;
	
	free_expression(this->expression);
	
	EXIT;
}

