
#include <assert.h>

#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_dict_index_expression(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct dict_index_expression* this = (void*) super;
	
	free_expression(this->list);
	
	free_expression(this->index);
	#endif
	
	EXIT;
}

