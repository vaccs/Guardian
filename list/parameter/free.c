
#include <stdlib.h>

#include <debug.h>

#include <parameter/free.h>

#include "struct.h"
#include "free.h"

void free_parameter_list(
	struct parameter_list* this)
{
	if (this && !--this->refcount)
	{
		while (this->n--) free_parameter(this->data[this->n]);
		
		free(this->data);
		free(this);
	}
}

