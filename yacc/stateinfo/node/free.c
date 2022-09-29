
#include <stdlib.h>

#include <debug.h>

#include <set/unsigned/free.h>

#include "struct.h"
#include "free.h"

void free_stateinfo_node(void* ptr)
{
	ENTER;
	
	struct stateinfo_node* node = ptr;
	
	free_unsignedset(node->tokens);
	
	free(node);
	
	EXIT;
}


