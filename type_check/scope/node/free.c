
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <value/free.h>

#include "struct.h"
#include "free.h"

void free_type_check_scope_node(void* ptr)
{
	ENTER
	
	struct type_check_scope_node* node = ptr;
	
	free_string(node->name);
	
	free_value(node->value);
	
	free(node);
	
	EXIT;
}
