
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_len_expression(
	struct expression* super)
{
	ENTER;
	
	struct len_expression* this = (void*) super;
	
	free_expression(this->list);
	
	EXIT;
}

