
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct statement_list* inc_statement_list(
	struct statement_list* this)
{
	if (this) this->refcount++;
	return this;
}

