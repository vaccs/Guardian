
#include <debug.h>

#include "../tokenizer/struct.h"

#include "primary/string.h"
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
			TODO;
			break;
		
		case t_string:
		{
			retval = read_grammar_primary_string_expression(tokenizer, scope, lex);
			break;
		}
		
		case t_oparen:
			TODO;
			break;
			
		default:
			TODO;
			break;
	}
	
	EXIT;
	return retval;
}


