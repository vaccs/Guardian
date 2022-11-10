
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct named_expression_list* inc_named_expression_list(
	struct named_expression_list* this)
{
	if (this) this->refcount++;
	return this;
}


