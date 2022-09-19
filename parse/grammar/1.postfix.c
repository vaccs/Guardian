
#include <debug.h>

#include <gegex/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "0.primary.h"
#include "1.postfix.h"

struct gbundle read_grammar_postfix_expression(
	struct tokenizer* tokenizer,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_grammar_primary_expression(tokenizer, lex);
	
	switch (tokenizer->token)
	{
		case t_asterisk:
			gegex_add_lambda_transition(retval.start, retval.accept);
			gegex_add_lambda_transition(retval.accept, retval.start);
			read_token(tokenizer);
			break;
		
		case t_plus:
			TODO;
			break;
		
		case t_qmark:
			gegex_add_lambda_transition(retval.start, retval.accept);
			read_token(tokenizer);
			break;
		
		case t_ocurly:
			TODO;
			break;
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}


