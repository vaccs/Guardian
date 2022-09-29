
#include <debug.h>

#include "struct.h"
#include "set_kind.h"

void regex_set_kind(
	struct regex* state,
	unsigned accepts,
	enum token_kind kind)
{
	ENTER;
	
	if (state->kind != kind)
	{
		state->kind = kind;
		
		if (state->accepts)
			state->accepts = accepts;
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* to = state->transitions[i];
			
			if (to)
			{
				regex_set_kind(to, accepts, kind);
			}
		}
		
		for (unsigned i = 0, n = state->lambdas.n; i < n; i++)
		{
			struct regex* to = state->lambdas.data[i];
			
			TODO;
		}
		
		if (state->EOF_transition_to)
		{
			regex_set_kind(state->EOF_transition_to, accepts, kind);
		}
	}
	
	EXIT;
}

