
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct zpexpressionset* inc_zpexpressionset(struct zpexpressionset* this)
{
	if (this)
		this->refcount++;
	return this;
}

