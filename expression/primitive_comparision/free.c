
#include <debug.h>

#include <type/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_primitive_comparision_expression(
	struct expression* super)
{
	ENTER;
	
	struct comparison_expression* this = (void*) super;
	
	free_expression(this->left);
	
	free_expression(this->right);
	
	free_type(this->type);
	
	EXIT;
}

