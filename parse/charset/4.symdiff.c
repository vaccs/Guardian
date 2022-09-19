
#include <debug.h>

#include "../tokenizer/struct.h"

#include "3.intersection.h"
#include "4.symdiff.h"

charset_t read_charset_symdiff_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	charset_t left = read_charset_intersection_expression(tokenizer);
	
	while (tokenizer->token == t_caret)
	{
		TODO;
	}
	
	EXIT;
	return left;
}
