
#include <debug.h>

#include <regex/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "2.juxtaposition.h"
#include "3.union.h"

struct rbundle read_regex_union_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	struct rbundle left = read_regex_juxtaposition_expression(tokenizer);
	
	while (tokenizer->token == t_vbar)
	{
		read_token(tokenizer);
		
		struct rbundle right = read_regex_juxtaposition_expression(tokenizer);
		
		regex_add_lambda_transition(left.start, right.start);
		
		regex_add_lambda_transition(right.accept, left.accept);
	}
	
	EXIT;
	return left;
}
