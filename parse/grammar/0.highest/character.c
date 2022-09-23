
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

#include "../../parser.h"
#include "../../misc/escapes.h"

#include "string.h"

struct gbundle read_grammar_highest_character(
	struct lex* lex,
	struct zebu_grammar_highest* highest)
{
	ENTER;
	
	struct token* character = highest->character;
	
	assert(character);
	
	escapes(character->data, character->len);
	
	unsigned char code = character->data[0];
	
	dpvc(code);
	
	struct rbundle regex = new_regex_from_string(&code, 1);
	
	unsigned token_id = lex_add_token(lex, regex.start, tk_literal);
	
	dpv(token_id);
	
	dpv(highest->tags.n);
	
	struct structinfo* structinfo = new_structinfo();
	
	struct unsignedset* whitespace = new_unsignedset();
	
	struct gegex *start = new_gegex(), *end = new_gegex();
	
	for (unsigned i = 0, n = highest->tags.n; i < n; i++)
	{
		struct token* token = highest->tags.data[i];
		
		dpvsn(token->data, token->len);
		
		struct string* tag = new_string_from_token(token);
		
		if (token->data[token->len - 1] == ']')
			structinfo_add_field(structinfo, tag, NULL, snt_token_array);
		else
			structinfo_add_field(structinfo, tag, NULL, snt_token_scalar);
		
		free_string(tag);
	}
	
	if (lex->whitespace_token_id)
	{
		unsignedset_add(whitespace, lex->whitespace_token_id);
	}
	
	gegex_add_transition(start, token_id, whitespace, structinfo, end);
	
	free_unsignedset(whitespace);
	
	free_structinfo(structinfo);
	
	EXIT;
	return (struct gbundle) {start, end};
	
}



















