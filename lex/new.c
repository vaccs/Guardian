
#include <debug.h>

#include "token_to_id_node/compare.h"
#include "token_to_id_node/free.h"

#include "struct.h"
#include "new.h"

struct lex* new_lex()
{
	ENTER;
	
	struct lex* this = smalloc(sizeof(*this));
	
	this->token_to_id = avl_alloc_tree(compare_token_to_id_nodes, free_token_to_id_node);
	
	this->next_id = 1; // 0 indicates error
	
	this->whitespace_token_id = 0; // 0 indicates no whitespace
	
	EXIT;
	return this;
}
