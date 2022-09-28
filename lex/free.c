
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_lex(struct lex* this)
{
	ENTER;
	
	avl_free_tree(this->token_to_id);
	
	free(this);
	
	EXIT;
}

