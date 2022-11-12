
#include <debug.h>

#include <list/value/free.h>

#include "struct.h"
#include "free.h"

void free_set_value(
	struct value* super)
{
	ENTER;
	
	struct set_value* this = (void*) super;
	
	free_value_list(this->elements);
	
	EXIT;
}

