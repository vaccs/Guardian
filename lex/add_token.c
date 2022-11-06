
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <regex/set_kind.h>
#include <regex/free.h>

#include "token_to_id_node/struct.h"
#include "token_to_id_node/new.h"

#include "id_to_token_node/struct.h"
#include "id_to_token_node/new.h"

#include "struct.h"
#include "add_token.h"

unsigned lex_add_token(
	struct lex* this,
	struct regex* token,
	enum token_kind kind)
{
	unsigned retval;
	ENTER;
	
	dpv(token);
	
	dpv(kind);
	
	struct avl_node_t* node;
	
	if ((node = avl_search(this->token_to_id, &token)))
	{
		struct token_to_id_node* found = node->item;
		
		free_regex(token);
		
		retval = found->id;
	}
	else
	{
		retval = this->next_id++;
		
		regex_set_kind(token, retval, kind);
		
		avl_insert(this->token_to_id, new_token_to_id_node(token, retval));
		avl_insert(this->id_to_token, new_id_to_token_node(retval, token));
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}













