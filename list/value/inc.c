
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct value_list* inc_value_list(
	struct value_list* this)
{
	if (this) this->refcount++;
	return this;
}


