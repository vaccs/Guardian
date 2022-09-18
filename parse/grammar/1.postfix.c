
#include <debug.h>

#include "0.primary.h"
#include "1.postfix.h"

struct gbundle read_grammar_postfix_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_grammar_primary_expression(tokenizer, scope, lex);
	
	TODO;
	
	EXIT;
}


