
#include <debug.h>

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"

#include "grammar/4.root.h"

#include "read_grammar_rule.h"

void read_grammar_rule(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex,
	struct string* name)
{
	ENTER;
	
	assert(tokenizer->token == t_colon);
	
	read_token(tokenizer);
	
	struct gbundle bundle = read_grammar_root_expression(tokenizer, scope, lex);
	
	TODO;
	
	EXIT;
}

