
#include <debug.h>

#include <regex/new_from_string.h>
#include <regex/nfa_to_dfa.h>
#include <regex/free.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include <gegex/new.h>
#include <gegex/add_transition.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/free.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/free.h>

#include "../../tokenizer/struct.h"
#include "../../tokenizer/read_token.h"

#include "character.h"

struct gbundle read_grammar_primary_character_expression(
	struct tokenizer* tokenizer,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_character);
	
	unsigned char code = tokenizer->tokenchars.chars[0];
	
	dpvc(code);
	
	struct rbundle nfa = new_regex_from_string(&code, 1);
	
	struct regex* dfa = regex_nfa_to_dfa(nfa);
	
	unsigned token_id = lex_add_token(lex, dfa, tk_literal);
	
	dpv(token_id);
	
	struct gegex* start = new_gegex();
	
	struct gegex* end = new_gegex();
	
	struct structinfo* structinfo = new_structinfo();
	
	read_token(tokenizer);
	
	while (false
		|| tokenizer->token == t_scalar_hashtag
		|| tokenizer->token == t_array_hashtag)
	{
		TODO;
		#if 0
		struct string* tag = new_string_from_tokenchars(tokenizer);
		
		switch (tokenizer->token)
		{
			case t_scalar_hashtag:
			{
				structinfo_add_field(structinfo, tag, snt_token_string_scalar);
				break;
			}
			
			case t_array_hashtag:
			{
				TODO;
				#if 0
				structinfo_add_token_array_field(structinfo, tag);
				#endif
				break;
			}
			
			default:
				TODO;
				break;
		}
		
		read_token(tokenizer);
		
		free_string(tag);
		#endif
	}
	
	struct unsignedset* whitespace = new_unsignedset();
	
	if (lex->whitespace_token_id)
	{
		unsignedset_add(whitespace, lex->whitespace_token_id);
	}
	
	gegex_add_transition(start, token_id, whitespace, structinfo, end);
	
	free_unsignedset(whitespace);
	
	free_structinfo(structinfo);
	
	free_regex(nfa.start);
	
	EXIT;
	return (struct gbundle) {start, end};
}















