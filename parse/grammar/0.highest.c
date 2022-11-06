
#include <assert.h>

#include <debug.h>

#include "../parse.h"

#include "3.root.h"

#include "0.highest/character.h"
#include "0.highest/string.h"
#include "0.highest/regex.h"
#include "0.highest/name.h"
#include "0.highest.h"

struct gbundle read_grammar_highest(
	struct lex* lex,
	struct zebu_grammar_highest* highest)
{
	struct gbundle retval;
	ENTER;
	
	if (highest->character)
		retval = read_grammar_highest_character(lex, highest);
	else if (highest->integer)
	{
		TODO;
	}
	else if (highest->string)
		retval = read_grammar_highest_string(lex, highest);
	else if (highest->name)
		retval = read_grammar_highest_name(lex, highest);
	else if (highest->regex)
		retval = read_grammar_highest_regex(lex, highest);
	else if (highest->charset)
	{
		TODO;
	}
	else if (highest->subgrammar)
		retval = read_grammar_root(lex, highest->subgrammar);
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}











