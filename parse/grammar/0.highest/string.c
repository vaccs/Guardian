
#include <debug.h>

#include <regex/new_from_string.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_field.h>
#include <yacc/structinfo/free.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/free.h>

#include <gegex/new.h>
#include <gegex/add_transition.h>

#include "../../parse.h"
#include "../../misc/escapes.h"

#include "string.h"

struct gbundle read_grammar_highest_string(
	struct lex* lex,
	struct zebu_grammar_highest* highest)
{
	ENTER;
	
	struct zebu_token* string = highest->string;
	
	assert(string);
	
	dpvsn(string->data, string->len);
	
	string->len = escapes(string->data, string->len);
	
	dpvsn(string->data, string->len);
	
	struct rbundle regex = new_regex_from_string(string->data, string->len);
	
	unsigned token_id = lex_add_token(lex, regex.start, tk_literal);
	
	dpv(token_id);
	
	dpv(highest->tags.n);
	
	struct structinfo* structinfo = new_structinfo();
	
	struct gegex *start = new_gegex(), *end = new_gegex();
	
	for (unsigned i = 0, n = highest->tags.n; i < n; i++)
	{
		struct zebu_token* token = highest->tags.data[i];
		
		dpvsn(token->data, token->len);
		
		struct string* tag = new_string_from_token(token);
		
		if (token->data[token->len - 1] == ']')
			structinfo_add_field(structinfo, tag, NULL, snt_token_array);
		else
			structinfo_add_field(structinfo, tag, NULL, snt_token_scalar);
		
		free_string(tag);
	}
	
	gegex_add_transition(start, token_id, structinfo, end);
	
	free_structinfo(structinfo);
	
	EXIT;
	return (struct gbundle) {start, end};
}



















