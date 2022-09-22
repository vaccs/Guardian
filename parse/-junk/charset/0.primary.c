
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "0.primary.h"

charset_t read_charset_primary_expression(
	struct tokenizer* tokenizer)
{
	charset_t retval = {};
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character:
		{
			unsigned char first = *tokenizer->tokenchars.chars;
			
			dpvc(first);
			
			retval[first >> 4] |= 1 << (first & 0xF);
			break;
		}
		
		case t_octal_literal:
		{
			TODO;
			break;
		}
		
		case t_decimal_literal:
			TODO;
			break;
		
		case t_hexadecimal_literal:
			TODO;
			break;
		
		default:
			TODO;
			break;
	}
	
	read_token(tokenizer);
	
	EXIT;
	return retval;
}













