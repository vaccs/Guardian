
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_raw_declaration(
	struct raw_declaration* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		TODO;
	}
	
	EXIT;
}

