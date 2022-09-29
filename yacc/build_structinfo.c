

#include <debug.h>

/*#include <avl/foreach.h>*/

#include <gegex/grammar/struct.h>
#include <gegex/transition/struct.h>
#include <gegex/struct.h>

/*#include <named/gegex/struct.h>*/

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

/*#include <set/string/foreach.h>*/

/*#include <set/ptr/new.h>*/
/*#include <set/ptr/add.h>*/
/*#include <set/ptr/free.h>*/
/*#include <set/gegex/clear.h>*/

#include "structinfo/new.h"
#include "structinfo/update.h"
/*#include "structinfo/to_string.h"*/
/*#include "structinfo/to_hashtagstring.h"*/
/*#include "structinfo/add_token_field.h"*/
/*#include "structinfo/add_grammar_field.h"*/
/*#include "structinfo/compare.h"*/
/*#include "structinfo/free.h"*/

#include "build_structinfo.h"

struct structinfo* build_structinfo(
	struct string* name,
	struct gegex* start)
{
	ENTER;
	
	struct ptrset* queued = new_ptrset();
	
	struct quack* todo = new_quack();
	
	struct structinfo* info = new_structinfo();
	
	ptrset_add(queued, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* const transition = state->transitions.data[i];
			
			structinfo_update(info, transition->structinfo);
			
			if (ptrset_add(queued, transition->to))
				quack_append(todo, transition->to);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* const transition = state->grammars.data[i];
			
			structinfo_update(info, transition->structinfo);
			
			if (ptrset_add(queued, transition->to))
				quack_append(todo, transition->to);
		}
	}
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	EXIT;
	return info;
}




























