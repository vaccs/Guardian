
#include <debug.h>

#include "5.union.h"
#include "6.root.h"

charset_t read_charset_root_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	charset_t retval = read_charset_union_expression(tokenizer);
	
	EXIT;
	return retval;
}
