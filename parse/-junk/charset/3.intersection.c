
#include <debug.h>

#include "../tokenizer/struct.h"

#include "2.range.h"
#include "3.intersection.h"

charset_t read_charset_intersection_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	charset_t left = read_charset_range_expression(tokenizer);
	
	while (tokenizer->token == t_ampersand)
	{
		TODO;
	}
	
	EXIT;
	return left;
}
