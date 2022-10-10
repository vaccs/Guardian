
#include <debug.h>

#include <out/type/free.h>

#include "struct.h"
#include "free.h"

void free_type_lookup_node(void* ptr)
{
	struct type_lookup_node* node = ptr;
	
	free_out_type(node->otype);
	
	free(node);
}

