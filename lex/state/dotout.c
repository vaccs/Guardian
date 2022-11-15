
#ifdef DOTOUT

#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include <debug.h>

#include <defines/argv0.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include <misc/framecounter.h>

#include "struct.h"
#include "dotout.h"

void lex_state_dotout(
	struct lex_state* start)
{
	ENTER;
	
	char path[PATH_MAX];
	
	sprintf(path, "dot/%u.dot", framecounter++);
	
	FILE* stream = fopen(path, "w");
	
	if (!stream)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, path);
		abort();
	}
	
	fprintf(stream, ""
		"digraph {"
			"rankdir = \"LR\"" "\n"
			"label = \"%s\"" "\n"
	"", __PRETTY_FUNCTION__);
	
	assert(start);
	
	struct quack* todo = new_quack();
	
	struct ptrset* queued = new_ptrset();
	
	quack_append(todo, start);
	
	ptrset_add(queued, start);
	
	while (quack_is_nonempty(todo))
	{
		struct lex_state* state = quack_pop(todo);
		
		fprintf(stream, ""
			"\"%p\" [" "\n"
				"label = \"\"" "\n"
				"shape = %s" "\n"
			"];"
		"", state, state->accepts ? "doublecircle" : "circle");
		
		for (unsigned i = 0; i < 256; i++)
		{
			struct lex_state* to = state->transitions[i];
			
			if (to)
			{
				fprintf(stream, ""
					"\"%p\" -> \"%p\" ["
						"label = \"%u\""
					"];"
				"", state, to, i);
				
				if (ptrset_add(queued, to))
					quack_append(todo, to);
			}
		}
		
		if (state->EOF_transition_to)
		{
			struct lex_state* to = state->EOF_transition_to;
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" ["
					"label = \"<EOF>\""
				"];"
			"", state, to);
			
			if (ptrset_add(queued, to))
				quack_append(todo, to);
		}
	}
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	fprintf(stream, ""
		"}"
	"");
	
	fclose(stream);
	
	EXIT;
}


#endif
