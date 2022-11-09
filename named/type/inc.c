
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct named_type* inc_named_type(
	struct named_type* this)
{
	ENTER;
	if (this)
		this->refcount++;
	EXIT;
	return this;
}

