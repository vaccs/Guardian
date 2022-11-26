
#include <debug.h>

#include <regex/struct.h>

#include <value/bool/new.h>

#include <value/string/struct.h>

#include "run.h"

struct value* regex_match_run(
	struct type* type,
	struct string_value* string,
	struct regex* regex)
{
	ENTER;
	
	unsigned char* moving = string->chars;
	unsigned n = string->len;
	
	while (regex && n) regex = regex->transitions[n--, *moving++];
	
	struct value* value = new_bool_value(type, regex && regex->accepts);
	
	EXIT;
	return value;
}

