
#include <debug.h>

#include <regex/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "0.primary.h"
#include "1.postfix.h"

struct rbundle read_regex_postfix_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	struct rbundle left = read_regex_primary_expression(tokenizer);
	
	switch (tokenizer->token)
	{
		case t_plus:
			TODO;
			break;
		
		case t_asterisk:
			regex_add_lambda_transition(left.start, left.accept);
			regex_add_lambda_transition(left.accept, left.start);
			read_token(tokenizer);
			break;
		
		case t_qmark:
			regex_add_lambda_transition(left.start, left.accept);
			read_token(tokenizer);
			break;
		
		case t_ocurly:
			TODO;
			break;
		
		default:
			break;
	}
	
	EXIT;
	return left;
}



