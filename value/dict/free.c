
#include <assert.h>

#include <debug.h>

/*#include <dict/value/free.h>*/

#include "struct.h"
#include "free.h"

void free_dict_value(
	struct value* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct dict_value* this = (void*) super;
	
	free_value_dict(this->elements);
	#endif
	
	EXIT;
}

