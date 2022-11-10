
#include <debug.h>

#include <regex/add_lambda_transition.h>

#include "../parser.h"

#include "2.juxtaposition.h"
#include "3.root.h"

struct rbundle process_regex_root(struct zebu_regex* regex)
{
	ENTER;
	
	struct rbundle base = process_regex_juxaposition(regex->base);
	
	for (unsigned i = 0, n = regex->ors.n; i < n; i++)
	{
		struct rbundle or = process_regex_juxaposition(regex->ors.data[i]);
		
		regex_add_lambda_transition(base.start, or.start);
		
		regex_add_lambda_transition(or.accepts, base.accepts);
	}
	
	EXIT;
	return base;
}
