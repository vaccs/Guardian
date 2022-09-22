
#include <debug.h>

#include "3.union.h"
#include "4.root.h"

struct gbundle read_grammar_root_expression(
	struct tokenizer* tokenizer,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_grammar_union_expression(tokenizer, lex);
	
	EXIT;
	return retval;
}


