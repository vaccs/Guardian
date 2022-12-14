
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_dict_math_expression(
	struct expression* super)
{
	ENTER;
	
	struct dict_math_expression* this = (void*) super;
	
	free_expression(this->left);
	
	free_expression(this->right);
	
	EXIT;
}

