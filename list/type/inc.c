
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct type_list* inc_type_list(
	struct type_list* this)
{
	if (this) this->refcount++;
	return this;
}


