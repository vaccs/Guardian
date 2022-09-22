
#include <debug.h>

#include "3.union.h"
#include "4.root.h"

struct rbundle read_regex_root_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	struct rbundle retval = read_regex_union_expression(tokenizer);
	
	EXIT;
	return retval;
}

