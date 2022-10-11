
#include <debug.h>

#include "../struct.h"

#include "char.h"
#include "list.h"
#include "charlist.h"

struct type* type_cache_get_charlist_type(
	struct type_cache* this)
{
	ENTER;
	
	if (!this->charlist_type)
	{
		struct type* ctype = type_cache_get_char_type(this);
		
		struct type* type = type_cache_get_list_type(this, ctype);
		
		this->charlist_type = type;
	}
	
	EXIT;
	return this->charlist_type;
}

