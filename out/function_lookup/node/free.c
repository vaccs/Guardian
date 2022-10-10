
#include <debug.h>

#include <out/function/free.h>

#include "struct.h"
#include "free.h"

void free_function_lookup_node(void* ptr)
{
	struct function_lookup_node* node = ptr;
	
	free_out_function(node->function);
	
	free(node);
}

