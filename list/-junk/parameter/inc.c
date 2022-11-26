
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct parameter_list* inc_parameter_list(
	struct parameter_list* this)
{
	if (this) this->refcount++;
	return this;
}


