
#include <debug.h>

#include "struct.h"
#include "new.h"

struct id_to_token_node* new_id_to_token_node(
	unsigned id,
	struct regex* token)
{
	ENTER;
	
	struct id_to_token_node* this = smalloc(sizeof(*this));
	
	this->id = id;
	this->token = token;
	
	EXIT;
	return this;
}

