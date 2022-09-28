
#include <debug.h>

#include <parse/parse.h>

#include "struct.h"
#include "free.h"

void free_named_zebu_expression(void* ptr)
{
	ENTER;
	
	struct named_zebu_expression* this = ptr;
	
	free_string(this->name);
	
	free_zebu_expression(this->expression);
	
	free(this);
	
	EXIT;
}

