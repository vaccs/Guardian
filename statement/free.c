
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_statement(
	struct statement* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		switch (this->kind)
		{
			case sk_assertion:
				free_expression(this->expression);
				break;
			
			case sk_declaration:
				free_string(this->name);
				free_expression(this->expression);
				break;
			
			case sk_print:
				free_expression(this->expression);
				break;
			
			default:
				TODO;
				break;
		}
		
		free(this);
	}
	
	EXIT;
}

