
#include <debug.h>

#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>
#include <gegex/free.h>

#include <named/grammar/new.h>

#include "grammar/3.root.h"
#include "parser.h"
#include "start.h"

void process_start(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct zebu_start_directive* directive)
{
	ENTER;
	
	assert(directive->grammar);
	
	struct string* name = new_string("$start", 6);
	
	dpvs(name);
	
	if (avl_search(grammar, &name))
	{
		TODO;
		exit(1);
	}
	
	struct gbundle nfa = read_grammar_root(lex, directive->grammar);
	
	struct gegex* dfa = gegex_nfa_to_dfa(nfa);
	
	struct gegex* simp = gegex_simplify_dfa(dfa);
	
	avl_insert(grammar, new_named_grammar(name, simp));
	
	free_gegex(nfa.start);
	
	free_string(name);
	
	free_gegex(dfa);
	
	EXIT;
}

