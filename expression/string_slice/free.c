
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_string_slice_expression(
	struct expression* super)
{
	ENTER;
	
	struct string_slice_expression* this = (void*) super;
	
	free_expression(this->string);
	
	free_expression(this->startindex);
	
	free_expression(this->endindex);
	
	EXIT;
}

