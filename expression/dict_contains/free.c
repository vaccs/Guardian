
#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_dict_contains_expression(
	struct expression* super)
{
	struct dict_contains_expression* const this = (void*) super;
	ENTER;
	
	free_expression(this->key);
	
	free_expression(this->dict);
	
	EXIT;
}

