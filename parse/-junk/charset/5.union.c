
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "4.symdiff.h"
#include "5.union.h"

charset_t read_charset_union_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	charset_t left = read_charset_symdiff_expression(tokenizer);
	
	again: switch (tokenizer->token)
	{
		case t_vbar:
		case t_comma:
			read_token(tokenizer);
		case t_character:
		case t_octal_literal:
		case t_decimal_literal:
		case t_hexadecimal_literal:
		case t_oparen:
		{
			charset_t right = read_charset_symdiff_expression(tokenizer);
			
			left |= right;
			break;
		}
		
		case t_csquare:
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return left;
}














