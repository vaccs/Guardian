
#include <assert.h>

#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_reduce_form_expression(
	struct expression* super)
{
	ENTER;
	
	struct reduce_form_expression* this = (void*) super;
	
	free_expression(this->lambda);
	
	free_expression(this->list);
	
	free_expression(this->initial);
	
	EXIT;
}

