
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct raw_statement_list* inc_raw_statement_list(
	struct raw_statement_list* this)
{
	if (this) this->refcount++;
	return this;
}

