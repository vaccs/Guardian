
#include <debug.h>

#include <gegex/add_lambda_transition.h>

#include "../tokenizer/struct.h"

#include "1.postfix.h"
#include "2.juxtaposition.h"

struct gbundle read_grammar_juxtaposition_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle left = read_grammar_postfix_expression(tokenizer, scope, lex);
	
	again: switch (tokenizer->token)
	{
		case t_oparen:
		case t_string:
		case t_character:
		{
			struct gbundle right = read_grammar_postfix_expression(tokenizer, scope, lex);
			
			gegex_add_lambda_transition(left.accepts, right.start);
			
			left = (struct gbundle) {left.start, right.accepts};
			goto again;
		}
		
		case t_semicolon:
		case t_cparen:
		case t_vbar:
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return left;
}


