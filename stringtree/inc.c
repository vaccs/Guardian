
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct stringtree* inc_stringtree(
	struct stringtree* this)
{
	if (this) this->refcount++;
	return this;
}

