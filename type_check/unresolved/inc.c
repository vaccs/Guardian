
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct unresolved* inc_unresolved(struct unresolved* this)
{
	this->refcount++;
	return this;
}

