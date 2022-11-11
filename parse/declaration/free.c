
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <string/free.h>

#include <parse/parse.h>

#include "struct.h"
#include "free.h"

void free_raw_declaration(
	struct raw_declaration* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		free_string(this->name);
		
		free_zebu_expression(this->expression);
		
		free(this);
	}
	
	EXIT;
}

