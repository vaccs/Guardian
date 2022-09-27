
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct expression* inc_expression(struct expression* this)
{
	if (this) this->refcount++;
	return this;
}

