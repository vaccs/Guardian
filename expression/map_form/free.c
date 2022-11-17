
#include <assert.h>

#include <debug.h>

#include <list/expression/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_map_form_expression(
	struct expression* super)
{
	ENTER;
	
	struct map_form_expression* this = (void*) super;
	
	free_expression(this->lambda);
	
	free_expression_list(this->arguments);
	
	EXIT;
}

