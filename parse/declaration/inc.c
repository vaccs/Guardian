
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct raw_declaration* inc_raw_declaration(
	struct raw_declaration* this)
{
	ENTER;
	
	if (this)
		this->refcount++;
	
	EXIT;
	return this;
}

