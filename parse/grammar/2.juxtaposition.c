
#include <debug.h>

#include <gegex/add_lambda_transition.h>

#include "../parse.h"

#include "1.postfix.h"
#include "2.juxtaposition.h"

struct gbundle read_grammar_juxtaposition(
	struct lex* lex,
	struct zebu_grammar_juxtaposition* juxtaposition)
{
	ENTER;
	
	struct gbundle base = read_grammar_postfix(lex, juxtaposition->base);
	
	for (unsigned i = 0, n = juxtaposition->juxtapositions.n; i < n; i++)
	{
		struct gbundle jux = read_grammar_postfix(lex, juxtaposition->juxtapositions.data[i]);
		
		gegex_add_lambda_transition(base.accepts, jux.start);
		
		base.accepts = jux.accepts;
	}
	
	EXIT;
	return base;
}
