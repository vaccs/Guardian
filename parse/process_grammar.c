
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <avl/insert.h>
#include <avl/search.h>

#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>
#include <gegex/combine_structinfos.h>
#include <gegex/free.h>

#include <yacc/structinfo/free.h>

#include <named/grammar/new.h>

#include <named/structinfo/new.h>

#include <type_cache/get_type/grammar.h>

#include <type/free.h>

#include "grammar/3.root.h"

#include "parse.h"
#include "process_grammar.h"

void process_grammar(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct zebu_grammar_rule* rule)
{
	ENTER;
	
	assert(rule->grammar);
	
	struct string* name = new_string_from_token(rule->name);
	
	dpvs(name);
	
	if (avl_search(grammar, &name))
	{
		TODO;
		exit(1);
	}
	
	struct gbundle nfa = read_grammar_root(lex, rule->grammar);
	
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














