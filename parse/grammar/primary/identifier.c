
#include <debug.h>

#include <gegex/new.h>
#include <gegex/add_grammar_transition.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_field.h>
#include <yacc/structinfo/free.h>

#include "../../tokenizer/struct.h"
#include "../../tokenizer/read_token.h"

#include "identifier.h"

struct gbundle read_grammar_primary_identifier_expression(
	struct tokenizer* tokenizer,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_identifier);
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct string* grammar = new_string_from_tokenchars(tokenizer);
	
	struct structinfo* structinfo = new_structinfo();
	
	read_token(tokenizer);
	
	while (false
		|| tokenizer->token == t_scalar_hashtag
		|| tokenizer->token == t_array_hashtag)
	{
		struct string* tag = new_string_from_tokenchars(tokenizer);
		
		switch (tokenizer->token)
		{
			case t_scalar_hashtag:
				structinfo_add_field(structinfo, tag, grammar, snt_grammar_scalar);
				break;
			
			case t_array_hashtag:
				structinfo_add_field(structinfo, tag, grammar, snt_grammar_array);
				break;
			
			default:
				TODO;
				break;
		}
		
		read_token(tokenizer);
		
		free_string(tag);
	}
	
	struct gegex* start = new_gegex();
	
	struct gegex* accept = new_gegex();
	
	gegex_add_grammar_transition(start, grammar, structinfo, accept);
	
	free_structinfo(structinfo);
	
	free_string(grammar);
	
	EXIT;
	return (struct gbundle) {start, accept};
}













