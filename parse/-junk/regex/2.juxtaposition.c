
#include <debug.h>

#include "../parser.h"

#include "1.postfix.h"
#include "2.juxtaposition.h"

struct rbundle process_regex_juxaposition(
	struct zebu_regex_juxtaposition* juxtaposition)
{
	ENTER;
	
	struct rbundle base = process_regex_postfix(juxtaposition->base);
	
	for (unsigned i = 0, n = juxtaposition->juxtapositions.n; i < n; i++)
	{
		TODO;
	}
	
	EXIT;
	return base;
}
