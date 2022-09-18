
#include <debug.h>

#include <gegex/struct.h>
#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>
#include <gegex/free.h>

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"

#include "grammar/4.root.h"

#include "read_grammar_rule.h"

void read_grammar_rule(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex,
	struct string* name)
{
	ENTER;
	
	assert(tokenizer->token == t_colon);
	
	read_token(tokenizer);
	
	struct gbundle nfa = read_grammar_root_expression(tokenizer, scope, lex);
	
	nfa.accepts->accepts = true;
	
	struct gegex* dfa = gegex_nfa_to_dfa(nfa.start);
	
	struct gegex* simp = gegex_simplify_dfa(dfa);
	
	// somehow combine all structinfos of this grammar...
	TODO;
	
	// scope_declare_type(scope, name, structinfo);
	TODO;
	
	// scope_declare_grammar(scope, name, simp_start);
	TODO;
	
	free_gegex(dfa);
	
	free_gegex(nfa.start);
	
	EXIT;
}













