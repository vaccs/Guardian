
#include <debug.h>

#include <gegex/new.h>
#include <gegex/add_lambda_transition.h>

#include "../parse.h"

#include "0.highest.h"
#include "1.postfix.h"

struct gbundle read_grammar_postfix(
	struct lex* lex,
	struct zebu_grammar_postfix* postfix)
{
	ENTER;
	
	struct gbundle base = read_grammar_highest(lex, postfix->base);
	
	if (postfix->plus)
	{
		gegex_add_lambda_transition(base.accepts, base.start);
		
		struct gegex* new_accepts = new_gegex();
		
		gegex_add_lambda_transition(base.accepts, new_accepts);
		
		base.accepts = new_accepts;
	}
	else if (postfix->qmark)
	{
		gegex_add_lambda_transition(base.start, base.accepts);
	}
	else if (postfix->star)
	{
		gegex_add_lambda_transition(base.start, base.accepts);
		gegex_add_lambda_transition(base.accepts, base.start);
		
		struct gegex* new_accepts = new_gegex();
		
		gegex_add_lambda_transition(base.accepts, new_accepts);
		
		base.accepts = new_accepts;
	}
	
	EXIT;
	return base;
}
