
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_implication_expression(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct implication_expression* this = (void*) super;
	
	free_expression(this->left);
	
	free_expression(this->right);
	#endif
	
	EXIT;
}

