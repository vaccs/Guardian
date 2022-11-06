
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct declaration* inc_declaration(
	struct declaration* this)
{
	ENTER;
	
	if (this)
	{
		this->refcount++;
	}
	
	EXIT;
	return this;
}

