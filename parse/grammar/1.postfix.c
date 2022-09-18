
#include <debug.h>

#include "../tokenizer/struct.h"

#include "0.primary.h"
#include "1.postfix.h"

struct gbundle read_grammar_postfix_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_grammar_primary_expression(tokenizer, scope, lex);
	
	switch (tokenizer->token)
	{
		case t_asterisk:
			TODO;
			break;
		case t_plus:
			TODO;
			break;
		case t_qmark:
			TODO;
			break;
		default:
			break;
	}
	
	EXIT;
	return retval;
}


