
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

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

#include <regex/new_from_string.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa.h>
#include <regex/free.h>

#include <misc/unescape.h>

#ifdef DOTOUT
#include <regex/dotout.h>
#endif

#include "../../parse.h"

#include "character.h"

struct gbundle read_grammar_highest_character(
	struct lex* lex,
	struct zebu_grammar_highest* highest)
{
	ENTER;
	
	struct zebu_token* character = highest->character;
	
	assert(character);
	
	unescape(character->data, character->len);
	
	unsigned char code = character->data[0];
	
	dpvc(code);
	
	struct rbundle nfa = new_regex_from_string(&code, 1);
	
	#ifdef DOTOUT
	regex_dotout(nfa.start, nfa.accepts);
	#endif
	
	struct regex* dfa = regex_nfa_to_dfa(nfa);
	
	#ifdef DOTOUT
	regex_dotout(dfa, NULL);
	#endif
	
	struct regex* simp = regex_simplify_dfa(dfa);
	
	#ifdef DOTOUT
	regex_dotout(simp, NULL);
	#endif
	
	unsigned token_id = lex_add_token(lex, simp, tk_literal);
	
	dpv(token_id);
	
	dpv(highest->tags.n);
	
	struct structinfo* structinfo = new_structinfo();
	
	struct gegex *start = new_gegex(), *end = new_gegex();
	
	for (unsigned i = 0, n = highest->tags.n; i < n; i++)
	{
		struct zebu_token* token = highest->tags.data[i];
		
		dpvsn(token->data, token->len);
		
		if (token->data[token->len - 1] == ']')
		{
			struct string* tag = new_string((char*) token->data + 1, token->len - 3);
			
			structinfo_add_field(structinfo, snt_token_array, tag, NULL, NULL);
			
			free_string(tag);
		}
		else
		{
			struct string* tag = new_string((char*) token->data + 1, token->len - 1);
			
			structinfo_add_field(structinfo, snt_token_scalar, tag, NULL, NULL);
			
			free_string(tag);
		}
	}
	
	gegex_add_transition(start, token_id, structinfo, end);
	
	free_regex(nfa.start), free_regex(dfa);
	
	free_structinfo(structinfo);
	
	EXIT;
	return (struct gbundle) {start, end};
	
}



















