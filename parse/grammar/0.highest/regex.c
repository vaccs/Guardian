
#include <debug.h>

#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa.h>
#include <regex/free.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_field.h>
#include <yacc/structinfo/free.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/free.h>

#include <gegex/new.h>
#include <gegex/add_transition.h>

#include "../../parse.h"
#include "../../regex.h"

#include "regex.h"

struct gbundle read_grammar_highest_regex(
	struct lex* lex,
	struct zebu_grammar_highest* highest)
{
	ENTER;
	
	assert(highest->regex);
	
	struct rbundle nfa = process_regex(highest->regex);
	
	struct regex* dfa = regex_nfa_to_dfa(nfa);
	
	struct regex* simp = regex_simplify_dfa(dfa);
	
	unsigned token_id = lex_add_token(lex, simp, tk_regex);
	
	dpv(token_id);
	
	struct structinfo* structinfo = new_structinfo();
	
	struct unsignedset* whitespace = new_unsignedset();
	
	struct gegex *start = new_gegex(), *end = new_gegex();
	
	for (unsigned i = 0, n = highest->tags.n; i < n; i++)
	{
		struct zebu_token* token = highest->tags.data[i];
		
		dpvsn(token->data, token->len);
		
		struct string* tag = new_string_from_token(token);
		
		if (token->data[token->len - 1] == ']')
			structinfo_add_field(structinfo, tag, NULL, snt_token_array);
		else
			structinfo_add_field(structinfo, tag, NULL, snt_token_scalar);
		
		free_string(tag);
	}
	
	if (lex->whitespace_token_id)
	{
		unsignedset_add(whitespace, lex->whitespace_token_id);
	}
	
	gegex_add_transition(start, token_id, whitespace, structinfo, end);
	
	free_unsignedset(whitespace);
	
	free_structinfo(structinfo);
	
	free_regex(nfa.start), free_regex(dfa);
	
	EXIT;
	return (struct gbundle) {start, end};
}















