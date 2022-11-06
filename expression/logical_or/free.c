
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_logical_or_expression(
	struct expression* super)
{
	ENTER;
	
	struct logical_or_expression* this = (void*) super;
	
	free_expression(this->left);
	
	free_expression(this->right);
	
	EXIT;
}

