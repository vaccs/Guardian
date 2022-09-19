
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "0.primary.h"
#include "1.complement.h"

charset_t read_charset_complement_expression(
	struct tokenizer* tokenizer)
{
	charset_t retval;
	ENTER;
	
	if (tokenizer->token == t_emark)
	{
		read_token(tokenizer);
		
		retval = read_charset_primary_expression(tokenizer);
		
		retval = ~retval;
	}
	else
	{
		retval = read_charset_primary_expression(tokenizer);
	}
	
	EXIT;
	return retval;
}
