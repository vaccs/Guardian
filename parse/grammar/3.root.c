
#include <debug.h>

#include <gegex/add_lambda_transition.h>

#include "../parse.h"

#include "2.juxtaposition.h"
#include "3.root.h"

struct gbundle read_grammar_root(
	struct lex* lex,
	struct zebu_grammar* grammar)
{
	ENTER;
	
	struct gbundle base = read_grammar_juxtaposition(lex, grammar->base);
	
	for (unsigned i = 0, n = grammar->ors.n; i < n; i++)
	{
		struct gbundle or = read_grammar_juxtaposition(lex, grammar->ors.data[i]);
		
		gegex_add_lambda_transition(base.start, or.start);
		
		gegex_add_lambda_transition(or.accepts, base.accepts);
	}
	
	EXIT;
	return base;
}
