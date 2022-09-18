
#include <debug.h>

#include <regex/set_kind.h>

#include "token_to_id_node/new.h"

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
		TODO;
		#if 0
		struct dfa_to_id_node* found = node->item;
		
		free_regex(token);
		
		retval = found->id;
		#endif
	}
	else
	{
		retval = this->next_id++;
		
		regex_set_kind(token, retval, kind);
		
		avl_insert(this->token_to_id, new_token_to_id_node(token, retval));
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}













