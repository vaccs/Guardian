
#ifdef DOTOUT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include <misc/framecounter.h>

#include <defines/argv0.h>

#include "struct.h"
#include "dotout.h"

void regex_dotout(
	struct regex* start,
	struct regex* end)
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
		struct regex* regex = quack_pop(todo);
		
		fprintf(stream, ""
			"\"%p\" [" "\n"
				"label = \"\"" "\n"
				"shape = %s" "\n"
				"peripheries = %u" "\n"
			"];"
		"", regex,
			regex->accepts ? "doublecircle" : "circle",
			regex->accepts ? 2 + regex->kind : 1);
		
		for (unsigned i = 0; i < 256; i++)
		{
			struct regex* to = regex->transitions[i];
			
			if (to)
			{
				fprintf(stream, ""
					"\"%p\" -> \"%p\" ["
						"label = \"%u\""
					"];"
				"", regex, to, i);
				
				if (ptrset_add(queued, to))
					quack_append(todo, to);
			}
		}
		
		for (unsigned i = 0, n = regex->lambdas.n; i < n; i++)
		{
			struct regex* to = regex->lambdas.data[i];
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" ["
					"label = \"λ\""
				"];"
			"", regex, to);
			
			if (ptrset_add(queued, to))
				quack_append(todo, to);
		}
		
		if (regex->EOF_transition_to)
		{
			TODO;
		}
	}
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	if (end)
	{
		fprintf(stream, ""
			"\"%p\" ["
				"shape = doublecircle"
			"];"
		"", end);
	}
	
	fprintf(stream, ""
		"}"
	"");
	
	fclose(stream);
	
	EXIT;
}

#endif







































