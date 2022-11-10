
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <avl/insert.h>
#include <avl/search.h>

#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>
#include <gegex/free.h>

#include <gegex/combine_structinfos.h>

#include <named/grammar/new.h>

#include <named/structinfo/new.h>

#include <yacc/structinfo/free.h>

#include "grammar/3.root.h"
#include "parse.h"
#include "start.h"

void process_start(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
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
	
	struct structinfo* structinfo = gegex_combine_structinfos(simp);
	
	avl_insert(types, new_named_structinfo(name, structinfo));
	
	free_structinfo(structinfo);
	
	free_gegex(nfa.start);
	
	free_string(name);
	
	free_gegex(dfa);
	
	EXIT;
}




