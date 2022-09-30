
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct scope* inc_scope(
	struct scope* this)
{
	if (this) this->refcount++;
	return this;
}

