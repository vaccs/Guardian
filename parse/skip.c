
#include <assert.h>

#include <debug.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include <regex/add_lambda_transition.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa.h>
#include <regex/free.h>

#include "regex.h"
#include "parse.h"
#include "skip.h"

void process_skip(
	struct lex* lex,
	struct zebu_skip_directive* directive)
{
	ENTER;
	
	assert(directive->regex);
	
	struct rbundle nfa = process_regex(directive->regex);
	
	regex_add_lambda_transition(nfa.accepts, nfa.start);
	
	struct regex* dfa = regex_nfa_to_dfa(nfa);
	
	struct regex* simp = regex_simplify_dfa(dfa);
	
	unsigned token_id = lex_add_token(lex, simp, tk_whitespace);
	
	dpv(token_id);
	
	lex->whitespace_token_id = token_id;
	
	free_regex(nfa.start), free_regex(dfa);
	
	EXIT;
}

















