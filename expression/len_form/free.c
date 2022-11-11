
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_len_form_expression(
	struct expression* super)
{
	ENTER;
	
	struct len_form_expression* this = (void*) super;
	
	free_expression(this->list);
	
	EXIT;
}

