
#include <debug.h>

#include "token_to_id_node/compare.h"
#include "token_to_id_node/free.h"

#include "id_to_token_node/compare.h"
#include "id_to_token_node/free.h"

#include "build_tokenizer/node/compare.h"
#include "build_tokenizer/node/free.h"

#include "struct.h"
#include "new.h"

struct lex* new_lex()
{
	ENTER;
	
	struct lex* this = smalloc(sizeof(*this));
	
	this->token_to_id = avl_alloc_tree(compare_token_to_id_nodes, free_token_to_id_node);
	
	this->id_to_token = avl_alloc_tree(compare_id_to_token_nodes, free_id_to_token_node);
	
	this->tokenizer_cache = avl_alloc_tree(compare_build_tokenizer_nodes, free_build_tokenizer_node);
	
	this->next_id = 1; // 0 indicates error
	
	this->whitespace_token_id = 0; // 0 indicates no whitespace
	
	this->EOF_token_id = 0;
	
	EXIT;
	return this;
}
