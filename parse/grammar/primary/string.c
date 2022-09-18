
#include <debug.h>

#include <regex/new_from_string.h>
#include <regex/nfa_to_dfa.h>
#include <regex/free.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/free.h>

#include <gegex/new.h>
#include <gegex/add_transition.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/free.h>

#include "../../tokenizer/struct.h"
#include "../../tokenizer/read_token.h"

#include "string.h"

struct gbundle read_grammar_primary_string_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_string);
	
	dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
	
	struct rbundle nfa = new_regex_from_string(
		/* chars:  */ tokenizer->tokenchars.chars,
		/* strlen: */ tokenizer->tokenchars.n);
	
	struct regex* dfa = regex_nfa_to_dfa(nfa);
	
	unsigned token_id = lex_add_token(lex, dfa, tk_literal);
	
	dpv(token_id);
	
	struct gegex* start = new_gegex();
	
	struct gegex* end = new_gegex();
	
	struct structinfo* structinfo = new_structinfo(/* name: */ NULL);
	
	read_token(tokenizer);
	
	while (false
		|| tokenizer->token == t_hashtag_scalar
		|| tokenizer->token == t_hashtag_array)
	{
		TODO;
		#if 0
		struct string* tag = new_string_from_tokenchars(tokenizer);
		
		switch (tokenizer->token)
		{
			case t_hashtag_scalar:
				structinfo_add_token_scalar_field(structinfo, tag);
				break;
			
			case t_hashtag_array:
				structinfo_add_token_array_field(structinfo, tag);
				break;
			
			default:
				TODO;
				break;
		}
		
		read_token(tokenizer, production_after_highest_machine);
		
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










