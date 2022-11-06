
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct assertion* inc_assertion(
	struct assertion* this)
{
	ENTER;
	
	if (this)
		this->refcount++;
	
	EXIT;
	return this;
}


