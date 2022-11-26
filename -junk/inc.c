
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct parameter* inc_parameter(
	struct parameter* this)
{
	if (this) this->refcount++;
	return this;
}

