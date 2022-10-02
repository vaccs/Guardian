
#include <debug.h>

#include <type/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_complex_comparison_expression(
	struct expression* super)
{
	ENTER;
	
	struct complex_comparison_expression* this = (void*) super;
	
	free_expression(this->left);
	
	free_expression(this->right);
	
	free_type(this->type);
	
	EXIT;
}

