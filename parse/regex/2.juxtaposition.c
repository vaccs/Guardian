
#include <debug.h>

#include <regex/add_lambda_transition.h>

#include "../tokenizer/struct.h"

#include "1.postfix.h"
#include "2.juxtaposition.h"

struct rbundle read_regex_juxtaposition_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	struct rbundle left = read_regex_postfix_expression(tokenizer);
	
	again: switch (tokenizer->token)
	{
		case t_character:
		case t_string:
		case t_oparen:
		{
			struct rbundle right = read_regex_postfix_expression(tokenizer);
			
			regex_add_lambda_transition(left.accept, right.start);
			
			left = (struct rbundle) { left.start, right.accept };
			goto again;
		}
		
		case t_vbar:
		case t_semicolon:
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return left;
}
