
#include <debug.h>

#include <type/char/new.h>

#include "../struct.h"

#include "int.h"

struct type* type_cache_get_char_type(
	struct type_cache* this)
{
	ENTER;
	
	if (!this->char_type)
	{
		struct type* type = new_char_type(this->next++);
		
		this->char_type = type;
	}
	
	EXIT;
	return this->char_type;
}

