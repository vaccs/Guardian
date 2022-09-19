
#include <debug.h>

#include <gegex/struct.h>
#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>
#include <gegex/combine_structinfos.h>
#include <gegex/free.h>

#include <yacc/structinfo/free.h>

#include <type_cache/get_type/grammar.h>

#include <parse/scope/declare/type.h>
#include <parse/scope/declare/grammar.h>

#include <type/free.h>

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"

#include "grammar/4.root.h"

#include "read_grammar_rule.h"

void read_grammar_rule(
	struct tokenizer* tokenizer,
	struct type_cache* tcache,
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
	
	struct structinfo* combined = gegex_combine_structinfos(simp);
	
	struct type* type = type_cache_get_grammar_type(tcache, combined);
	
	scope_declare_type(scope, name, type);
	
	scope_declare_grammar(scope, name, simp);
	
	if (tokenizer->token != t_semicolon)
	{
		TODO;
	}
	
	read_token(tokenizer);
	
	free_type(type);
	
	free_gegex(dfa);
	
	free_gegex(nfa.start);
	
	free_structinfo(combined);
	
	EXIT;
}













