
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct value* inc_value(struct value* this)
{
	if (this) this->refcount++;
	return this;
}

