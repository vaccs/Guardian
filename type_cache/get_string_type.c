
#include <debug.h>

#include <type/string/new.h>

#include "struct.h"
#include "get_string_type.h"

struct type* type_cache_get_string_type(
	struct type_cache* this)
{
	ENTER;
	
	if (!this->string_type)
	{
		struct type* type = new_string_type(this->next++);
		
		this->string_type = type;
	}
	
	EXIT;
	return this->string_type;
}

