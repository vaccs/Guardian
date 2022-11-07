
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_tuple_concat_expression(
	struct expression* super)
{
	ENTER;
	
	struct tuple_concat_expression* this = (void*) super;
	
	free_expression(this->left);
	
	free_expression(this->right);
	
	EXIT;
}

