
#include <debug.h>

#include "../struct.h"

#include <type/inc.h>
#include <type/bool/struct.h>
#include <type/bool/new.h>

#include "bool.h"

struct type* type_cache_get_bool_type(
	struct type_cache* this)
{
	ENTER;
	
	if (!this->bool_type)
	{
		this->bool_type = new_bool_type();
	}
	
	EXIT;
	return inc_type(this->bool_type);
}















