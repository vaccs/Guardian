
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct named_type_list* inc_named_type_list(
	struct named_type_list* this)
{
	if (this) this->refcount++;
	return this;
}


