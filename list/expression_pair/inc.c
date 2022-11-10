
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct expression_pair_list* inc_expression_pair_list(
	struct expression_pair_list* this)
{
	if (this) this->refcount++;
	return this;
}

