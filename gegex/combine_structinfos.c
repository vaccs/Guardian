
#include <debug.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/pop.h>
#include <quack/is_nonempty.h>
#include <quack/free.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/update.h>

#include "transition/struct.h"
#include "struct.h"
#include "combine_structinfos.h"

struct structinfo* gegex_combine_structinfos(struct gegex* start)
{
	ENTER;
	
	struct ptrset* queued = new_ptrset();
	struct quack* todo = new_quack();
	
	ptrset_add(queued, start);
	quack_append(todo, start);
	
	struct structinfo* combined = new_structinfo();
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* ele = state->transitions.data[i];
			
			structinfo_update(combined, ele->structinfo);
			
			if (ptrset_add(queued, ele->to))
				quack_append(todo, ele->to);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			TODO;
		}
	}
	
	free_quack(todo);
	free_ptrset(queued);
	
	EXIT;
	return combined;
}












