
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct named_expression* inc_named_expression(
	struct named_expression* this)
{
	ENTER;
	
	if (this) this->refcount++;
	
	EXIT;
	return this;
}

