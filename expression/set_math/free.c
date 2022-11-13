
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_set_math_expression(
	struct expression* super)
{
	ENTER;
	
	struct set_math_expression* this = (void*) super;
	
	free_expression(this->left);
	
	free_expression(this->right);
	
	EXIT;
}

