
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

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
	
	struct gegex *start = new_gegex(), *end = new_gegex();
	
	for (unsigned i = 0, n = highest->tags.n; i < n; i++)
	{
		struct zebu_token* token = highest->tags.data[i];
		
		dpvsn(token->data, token->len);
		
		if (token->data[token->len - 1] == ']')
		{
			TODO;
			#if 0
			struct string* tag = new_string_from_token(token);
			structinfo_add_field(structinfo, tag, NULL, snt_token_array);
			free_string(tag);
			#endif
		}
		else
		{
			struct string* tag = new_string((char*) token->data + 1, token->len - 1);
			
			structinfo_add_field(structinfo, snt_token_scalar, tag, NULL, highest->tokentype);
			
			free_string(tag);
		}
	}
	
	gegex_add_transition(start, token_id, structinfo, end);
	
	free_structinfo(structinfo);
	
	free_regex(nfa.start), free_regex(dfa);
	
	EXIT;
	return (struct gbundle) {start, end};
}















