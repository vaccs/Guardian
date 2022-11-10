
#include <debug.h>

#include <regex/new_from_string.h>

#include "../parser.h"

#include "../misc/escapes.h"

#include "../charset.h"

#include "0.highest.h"

struct rbundle process_regex_highest(
	struct zebu_regex_highest* highest)
{
	struct rbundle retval;
	ENTER;
	
	if (highest->character)
	{
		dpvsn(highest->character->data, highest->character->len);
		
		escapes(highest->character->data, highest->character->len);
		
		unsigned char code = highest->character->data[0];
		
		dpvc(code);
		
		retval = new_regex_from_string(&code, 1);
	}
	else if (highest->integer)
	{
		TODO;
	}
	else if (highest->string)
	{
		TODO;
	}
	else if (highest->subregex)
	{
		TODO;
	}
	else if (highest->charset)
	{
		charset_t charset = process_charset_root(highest->charset);
		
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}








