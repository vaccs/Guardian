
#include <debug.h>

#include <type/float/new.h>

#include "struct.h"
#include "get_float_type.h"

struct type* type_cache_get_float_type(
	struct type_cache* this)
{
	ENTER;
	
	if (!this->float_type)
	{
		struct type* type = new_float_type(this->next++);
		
		this->float_type = type;
	}
	
	EXIT;
	return this->float_type;
}

