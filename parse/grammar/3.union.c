
#include <debug.h>

#include "2.juxtaposition.h"
#include "3.union.h"

struct gbundle read_grammar_union_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_grammar_juxtaposition_expression(tokenizer, scope, lex);
	
	TODO;
	
	EXIT;
}


