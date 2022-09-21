
#include <debug.h>

#include <expression/free.h>

#include "../expression/17.root.h"

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "debug.h"

void process_debug_directive(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	assert(tokenizer->token == t_directive);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_colon)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	struct expression* expression = read_root_expression(tokenizer);
	
	TODO;
	
	free_expression(expression);
	
	EXIT;
}























