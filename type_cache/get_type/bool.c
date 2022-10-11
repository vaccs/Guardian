
#include <debug.h>

#include "../struct.h"

#include <type/bool/new.h>

#include "bool.h"

struct type* type_cache_get_bool_type(
	struct type_cache* this)
{
	ENTER;
	
	if (!this->bool_type)
	{
		struct type* type = new_bool_type(this->next++);
		
		this->bool_type = type;
	}
	
	EXIT;
	return this->bool_type;
}















