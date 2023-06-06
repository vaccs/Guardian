
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include "struct.h"

#include "id_to_token_node/struct.h"

#include "lookup_token.h"

struct regex* lex_lookup_token(
	struct lex* this,
	unsigned token_id)
{
	ENTER;
	
	dpv(token_id);
	
	struct avl_node_t* node = avl_search(this->id_to_token, &(struct id_to_token_node) {token_id});
	
	dpv(node);
	
	assert(node);
	
	struct id_to_token_node* dfi = node->item;
	
	struct regex* retval = dfi->token;
	
	dpv(retval);
	
	EXIT;
	return retval;
}

