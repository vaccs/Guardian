
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <string/free.h>

#include "struct.h"
#include "free.h"

void free_capture(
	struct capture* this)
{
	if (this && !--this->refcount)
	{
		free_string(this->name);
		free(this);
	}
}

