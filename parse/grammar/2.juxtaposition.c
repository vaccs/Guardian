
#include <debug.h>

#include "1.postfix.h"
#include "2.juxtaposition.h"

struct gbundle read_grammar_juxtaposition_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_grammar_postfix_expression(tokenizer, scope, lex);
	
	TODO;
	
	EXIT;
}


