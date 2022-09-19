
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct type* inc_type(struct type* this)
{
	if (this) this->refcount++;
	return this;
}

