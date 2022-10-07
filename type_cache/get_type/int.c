
#include <debug.h>

#include <type/int/new.h>
#include <type/inc.h>

#include "../struct.h"

#include "int.h"

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
	return inc_type(this->int_type);
}

