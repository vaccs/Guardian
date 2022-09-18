
#include <debug.h>

#include "../tokenizer/struct.h"

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
			TODO;
			break;
		
		case t_qmark:
			TODO;
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
