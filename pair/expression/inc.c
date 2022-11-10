
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct expression_pair* inc_expression_pair(
	struct expression_pair* this)
{
	ENTER;
	
	if (this) this->refcount++;
	
	EXIT;
	return this;
}

