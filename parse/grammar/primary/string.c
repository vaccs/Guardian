
#include <debug.h>

#include "../../tokenizer/struct.h"

#include "string.h"

struct gbundle read_grammar_primary_string_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_string);
	
	dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
	
	TODO;
	#if 0
	struct regex* regex_start = regex_from_literal(
		/* chars:  */ tokenizer->tokenchars.chars,
		/* strlen: */ tokenizer->tokenchars.n);
	
	unsigned token_id = lex_add_token2(lex, regex_start, tk_literal);
	
	dpv(token_id);
	
	struct structinfo* structinfo = new_structinfo(/* name: */ NULL);
	
	read_token(tokenizer, production_after_highest_machine);
	
	while (false
		|| tokenizer->token == t_hashtag_scalar
		|| tokenizer->token == t_hashtag_array)
	{
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
	}
	
	struct gegex* gegex_start = new_gegex();
	
	struct gegex* gegex_end = new_gegex();
	
	struct unsignedset* whitespace = new_unsignedset();
	
	if (lex->whitespace_token_id)
	{
		unsignedset_add(whitespace, lex->whitespace_token_id);
	}
	
	gegex_add_transition(gegex_start, token_id, whitespace, structinfo, gegex_end);
	
	#ifdef DOTOUT
	gegex_dotout(gegex_start, gegex_end, __PRETTY_FUNCTION__);
	#endif
	
	free_unsignedset(whitespace);
	
	free_structinfo(structinfo);
	
	EXIT;
	return (struct gbundle) {gegex_start, gegex_end};
	#endif
	
	EXIT;
}
