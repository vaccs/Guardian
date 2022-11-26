
#include <debug.h>

#include <type/int/new.h>

#include "struct.h"

#include "get_int_type.h"

struct type* type_cache_get_int_type(
	struct type_cache* this)
{
	ENTER;
	
	if (!this->int_type)
	{
		struct type* type = new_int_type(this->next++);
		
		this->int_type = type;
	}
	
	EXIT;
	return this->int_type;
}

