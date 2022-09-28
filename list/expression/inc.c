
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct expression_list* inc_expression_list(
	struct expression_list* this)
{
	if (this) this->refcount++;
	return this;
}

