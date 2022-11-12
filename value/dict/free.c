
#include <assert.h>

#include <debug.h>

#include <list/value_pair/free.h>

#include "struct.h"
#include "free.h"

void free_dict_value(
	struct value* super)
{
	ENTER;
	
	struct dict_value* this = (void*) super;
	
	free_value_pair_list(this->elements);
	
	EXIT;
}

