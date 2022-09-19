
#include <debug.h>

#include "../tokenizer/struct.h"

#include "primary/character.h"
#include "primary/string.h"
#include "primary/regex.h"
#include "primary/parenthesis.h"

#include "0.primary.h"

struct gbundle read_grammar_primary_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character:
			retval = read_grammar_primary_character_expression(tokenizer, scope, lex);
			break;
		
		case t_string:
			retval = read_grammar_primary_string_expression(tokenizer, scope, lex);
			break;
		
		case t_slash:
			retval = read_grammar_primary_regex_expression(tokenizer, scope, lex);
			break;
		
		case t_oparen:
			retval = read_grammar_primary_parenthesis_expression(tokenizer, scope, lex);
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return retval;
}


