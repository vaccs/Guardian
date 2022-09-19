
#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include "transition/struct.h"
#include "transition/free.h"
#include "grammar/struct.h"
#include "grammar/free.h"
#include "struct.h"
#include "free.h"

void free_gegex(struct gegex* start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	struct ptrset* queued = new_ptrset();
	
	ptrset_add(queued, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* ele = state->transitions.data[i];
			
			if (ptrset_add(queued, ele->to))
				quack_append(todo, ele->to);
			
			free_gegex_transition(ele);
		}
		
		for (unsigned i = 0, n = state->lambdas.n; i < n; i++)
		{
			struct gegex* to = state->lambdas.data[i];
			
			if (ptrset_add(queued, to))
				quack_append(todo, to);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* ele = state->grammars.data[i];
			
			if (ptrset_add(queued, ele->to))
				quack_append(todo, ele->to);
			
			free_gegex_grammar_transition(ele);
		}
		
		free(state->transitions.data);
		free(state->lambdas.data);
		free(state->grammars.data);
		
		free(state);
	}
	
	EXIT;
}










