
#include <debug.h>

#include <gegex/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "2.juxtaposition.h"
#include "3.union.h"

struct gbundle read_grammar_union_expression(
	struct tokenizer* tokenizer,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle left = read_grammar_juxtaposition_expression(tokenizer, lex);
	
	while (tokenizer->token == t_vbar)
	{
		read_token(tokenizer);
		
		struct gbundle right = read_grammar_juxtaposition_expression(tokenizer, lex);
		
		gegex_add_lambda_transition(left.start, right.start);
		gegex_add_lambda_transition(right.accept, left.accept);
	}
	
	EXIT;
	return left;
}


