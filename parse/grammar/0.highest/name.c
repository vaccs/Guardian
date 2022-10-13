
#include <debug.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_field.h>
#include <yacc/structinfo/free.h>

#include <gegex/new.h>
#include <gegex/add_grammar_transition.h>

#include "../../parse.h"

#include "name.h"

struct gbundle read_grammar_highest_name(
	struct lex* lex,
	struct zebu_grammar_highest* highest)
{
	ENTER;
	
	assert(highest->name);
	
	struct string* name = new_string_from_token(highest->name);
	
	struct structinfo* structinfo = new_structinfo();
	
	struct gegex *start = new_gegex(), *accepts = new_gegex();
	
	for (unsigned i = 0, n = highest->tags.n; i < n; i++)
	{
		struct zebu_token* token = highest->tags.data[i];
		
		dpvsn(token->data, token->len);
		
		if (token->data[token->len - 1] == ']')
		{
			struct string* tag = new_string((char*) token->data + 1, token->len - 3);
			
			dpvs(tag);
			
			structinfo_add_field(structinfo, snt_grammar_array, tag, name);
			
			free_string(tag);
		}
		else
		{
			struct string* tag = new_string((char*) token->data + 1, token->len - 1);
			
			dpvs(tag);
			
			structinfo_add_field(structinfo, snt_grammar_scalar, tag, name);
			
			free_string(tag);
		}
	}
	
	gegex_add_grammar_transition(start, name, structinfo, accepts);
	
	free_structinfo(structinfo);
	
	free_string(name);
	
	EXIT;
	return (struct gbundle) {start, accepts};
}












