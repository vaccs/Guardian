
#include <debug.h>

#include "../parser.h"

#include "0.highest.h"
#include "1.postfix.h"

struct rbundle process_regex_postfix(
	struct zebu_regex_postfix* postfix)
{
	ENTER;
	
	struct rbundle base = process_regex_highest(postfix->base);
	
	if (postfix->plus)
	{
		TODO;
	}
	else if (postfix->qmark)
	{
		TODO;
	}
	else if (postfix->star)
	{
		TODO;
	}
	
	EXIT;
	return base;
}
