
#include <debug.h>

#include <regex/free.h>

#include "struct.h"
#include "free.h"

void free_token_to_id_node(void* ptr)
{
	struct token_to_id_node* node = ptr;
	
	free_regex(node->token);
	
	free(node);
}

