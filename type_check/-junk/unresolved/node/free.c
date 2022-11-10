
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <set/zpexpression/free.h>

#include "struct.h"
#include "free.h"

void free_unresolved_node(void* ptr)
{
	ENTER;
	
	struct unresolved_node* this = ptr;
	
	if (this && !--this->refcount)
	{
		free_string(this->name);
		free_zpexpressionset(this->layers.current);
		free_zpexpressionset(this->layers.deeper);
		free(this);
	}
	
	EXIT;
}

