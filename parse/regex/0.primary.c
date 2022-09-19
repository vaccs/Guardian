
#include <debug.h>

#include <regex/new_from_string.h>
#include <regex/new_from_charset.h>

#include "../charset/6.root.h"

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "0.primary.h"

struct rbundle read_regex_primary_expression(
	struct tokenizer* tokenizer)
{
	struct rbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character:
		{
			unsigned char code = tokenizer->tokenchars.chars[0];
			
			retval = new_regex_from_string(&code, 1);
			
			read_token(tokenizer);
			break;
		}
		
		case t_octal_literal:
			TODO;
			break;
		
		case t_decimal_literal:
			TODO;
			break;
		
		case t_hexadecimal_literal:
			TODO;
			break;
		
		case t_string:
		{
			TODO;
			break;
		}
		
		case t_osquare:
		{
			read_token(tokenizer);
			
			charset_t charset = read_charset_root_expression(tokenizer);
			
			if (tokenizer->token != t_csquare)
			{
				TODO;
			}
			
			retval = new_regex_from_charset(charset);
			
			read_token(tokenizer);
			
			break;
		}
		
		case t_oparen:
		{
			TODO;
			break;
		}
		
		default:
		{
			TODO;
			break;
		}
	}
	
	EXIT;
	return retval;
}










