
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct value_pair* inc_value_pair(
	struct value_pair* this)
{
	ENTER;
	
	if (this) this->refcount++;
	
	EXIT;
	return this;
}

