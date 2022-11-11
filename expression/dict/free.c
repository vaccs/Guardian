
#include <assert.h>

#include <debug.h>

#include <list/expression_pair/free.h>

#include "struct.h"
#include "free.h"

void free_dict_expression(
	struct expression* super)
{
	ENTER;
	
	struct dict_expression* this = (void*) super;
	
	free_expression_pair_list(this->elements);
	
	EXIT;
}

