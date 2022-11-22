
#include <debug.h>

#include <regex/free.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_regex_match_expression(
	struct expression* super)
{
	struct regex_match_expression* const this = (void*) super;
	ENTER;
	
	free_expression(this->expression);
	
	free_regex(this->regex);
	
	EXIT;
}

