
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct raw_statement* inc_raw_statement(
	struct raw_statement* this)
{
	ENTER;
	
	if (this)
	{
		this->refcount++;
	}
	
	EXIT;
	return this;
}

