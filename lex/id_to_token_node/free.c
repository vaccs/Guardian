
#include <debug.h>

#include <regex/free.h>

#include "struct.h"
#include "free.h"

void free_id_to_token_node(void* ptr)
{
	struct id_to_token_node* node = ptr;
	
	free(node);
}

