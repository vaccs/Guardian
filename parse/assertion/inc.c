
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct raw_assertion* inc_raw_assertion(
	struct raw_assertion* this)
{
	ENTER;
	
	if (this)
	{
		this->refcount++;
	}
	
	EXIT;
	return this;
}

