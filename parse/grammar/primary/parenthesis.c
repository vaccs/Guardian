
#include <debug.h>

#include "../../tokenizer/struct.h"
#include "../../tokenizer/read_token.h"

#include "../4.root.h"

#include "parenthesis.h"

struct gbundle read_grammar_primary_parenthesis_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_oparen);
	
	read_token(tokenizer);
	
	struct gbundle retval = read_grammar_root_expression(tokenizer, scope, lex);
	
	if (tokenizer->token != t_cparen)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	EXIT;
	return retval;
}
