
#include <debug.h>

#include "tokenizer/struct.h"

#include "read_value_declaration.h"

void read_value_declaration(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct string* name)
{
	ENTER;
	
	assert(tokenizer->token == t_equals);
	
	dpvs(name);
	
	TODO;
	
	EXIT;
}

