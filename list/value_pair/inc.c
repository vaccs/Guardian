
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct value_pair_list* inc_value_pair_list(
	struct value_pair_list* this)
{
	if (this) this->refcount++;
	return this;
}

