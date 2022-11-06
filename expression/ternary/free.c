
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_ternary_expression(
	struct expression* super)
{
	ENTER;
	
	struct ternary_expression* this = (void*) super;
	
	free_expression(this->conditional);
	free_expression(this->true_case);
	free_expression(this->false_case);
	
	EXIT;
}

