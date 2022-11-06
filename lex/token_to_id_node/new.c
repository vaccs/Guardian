
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct token_to_id_node* new_token_to_id_node(
	struct regex* token,
	unsigned id)
{
	ENTER;
	
	struct token_to_id_node* this = smalloc(sizeof(*this));
	
	this->token = token;
	this->id = id;
	
	EXIT;
	return this;
}

