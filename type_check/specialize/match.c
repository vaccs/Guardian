
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <type_cache/get_string_type.h>
#include <type_cache/get_bool_type.h>

#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa.h>
#include <regex/free.h>

#include <parse/parse.h>
#include <parse/regex.h>

#include <expression/struct.h>
#include <expression/regex_match/new.h>
#include <expression/free.h>

#include "equality.h"
#include "match.h"

struct expression* specialize_match_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_match_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->pattern)
	{
		struct expression* base = specialize_equality_expression(tcache, scope, zexpression->base);
		
		struct type* type = type_cache_get_string_type(tcache);
		
		if (base->type != type)
		{
			TODO;
			exit(1);
		}
		
		struct type* boolean = type_cache_get_bool_type(tcache);
		
		struct rbundle nfa = process_regex(zexpression->pattern);
		
		struct regex* dfa = regex_nfa_to_dfa(nfa);
		
		struct regex* simp = regex_simplify_dfa(dfa);
		
		if (base->kind == ek_literal)
		{
			TODO;
			
			free_regex(simp);
		}
		else
		{
			retval = new_regex_match_expression(boolean, base, simp);
		}
		
		free_regex(nfa.start);
		
		free_expression(base);
		
		free_regex(dfa);
	}
	else if (zexpression->base)
	{
		retval = specialize_equality_expression(tcache, scope, zexpression->base);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}













