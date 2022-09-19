
#include <debug.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa.h>
#include <regex/free.h>

#include "../regex/4.root.h"

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "skip.h"

void process_skip_directive(
	struct tokenizer* tokenizer,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_directive);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_colon)
	{
		TODO;
	}
	
	read_token(tokenizer);
	
	struct rbundle nfa = read_regex_root_expression(tokenizer);
	
	struct regex* dfa = regex_nfa_to_dfa(nfa);
	
	struct regex* simp = regex_simplify_dfa(dfa);
	
	unsigned token_id = lex_add_token(lex, simp, tk_whitespace);
	
	dpv(token_id);
	
	lex->whitespace_token_id = token_id;
	
	if (tokenizer->token != t_semicolon)
	{
		TODO;
	}
	
	read_token(tokenizer);
	
	free_regex(nfa.start);
	
	free_regex(dfa);
	
	EXIT;
}














