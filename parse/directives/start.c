
#include <debug.h>

#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>
#include <gegex/free.h>

#include <parse/scope/declare/grammar.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "../grammar/4.root.h"

#include "start.h"

void process_start_directive(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_directive);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_colon)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	struct string* name = new_string("$start");
	
	struct gbundle nfa = read_grammar_root_expression(tokenizer, lex);
	
	struct gegex* dfa = gegex_nfa_to_dfa(nfa);
	
	struct gegex* simp = gegex_simplify_dfa(dfa);
	
	scope_declare_grammar(scope, name, simp);
	
	if (tokenizer->token != t_semicolon)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	free_gegex(nfa.start), free_gegex(dfa);
	
	free_string(name);
	
	EXIT;
}
















