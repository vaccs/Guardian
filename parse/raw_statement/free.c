
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <parse/parse.h>

#include "struct.h"
#include "free.h"

void free_raw_statement(
	struct raw_statement* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		switch (this->kind)
		{
			case rsk_assertion:
				free_zebu_expression(this->expression);
				break;
			
			case rsk_declaration:
				free_string(this->name);
				free_zebu_expression(this->expression);
				break;
			
			case rsk_print:
				free_zebu_expression(this->expression);
				break;
			
			default:
				TODO;
				break;
		}
		
		free(this);
	}
	
	EXIT;
}

