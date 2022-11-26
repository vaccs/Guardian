
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <type/free.h>

#include "struct.h"
#include "free.h"

void free_parameter(
	struct parameter* this)
{
	if (this && !--this->refcount)
	{
		free_string(this->name);
		free(this);
	}
}

