
#include <debug.h>

#include <regex/new_from_string.h>
#include <regex/new_from_charset.h>
#include <regex/add_lambda_transition.h>

#include "misc/escapes.h"

#include "charset.h"
#include "parse.h"
#include "regex.h"

struct rbundle process_regex(struct zebu_regex* regex)
{
	ENTER;
	
	struct rbundle juxtaposition(struct zebu_regex_juxtaposition* juxtaposition)
	{
		ENTER;
		
		struct rbundle postfix(struct zebu_regex_postfix* postfix)
		{
			ENTER;
			
			struct rbundle highest(struct zebu_regex_highest* highest)
			{
				struct rbundle retval;
				ENTER;
				
				if (highest->character)
				{
					struct zebu_token* token = highest->character;
					
					dpvsn(token->data, token->len);
					
					escapes(token->data, token->len);
					
					unsigned char code = token->data[0];
					
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
					charset_t charset = process_charset(highest->charset);
					
					retval = new_regex_from_charset(charset);
				}
				else
				{
					TODO;
				}
				
				EXIT;
				return retval;
			}
			
			struct rbundle retval = highest(postfix->base);
			
			if (postfix->plus)
			{
				TODO;
			}
			else if (postfix->qmark)
			{
				regex_add_lambda_transition(retval.start, retval.accepts);
			}
			else if (postfix->star)
			{
				regex_add_lambda_transition(retval.start, retval.accepts);
				regex_add_lambda_transition(retval.accepts, retval.start);
				
				// fix this
				TODO;
			}
			
			EXIT;
			return retval;
		}
		
		struct rbundle retval = postfix(juxtaposition->base);
		
		for (unsigned i = 0, n = juxtaposition->juxtapositions.n; i < n; i++)
		{
			struct rbundle jux = postfix(juxtaposition->juxtapositions.data[i]);
			
			regex_add_lambda_transition(retval.accepts, jux.start);
			
			retval.accepts = jux.accepts;
		}
		
		EXIT;
		return retval;
	}
	
	struct rbundle retval = juxtaposition(regex->base);
	
	for (unsigned i = 0, n = regex->ors.n; i < n; i++)
	{
		struct rbundle or = juxtaposition(regex->ors.data[i]);
		
		regex_add_lambda_transition(retval.start, or.start);
		
		regex_add_lambda_transition(or.accepts, retval.accepts);
	}
	
	EXIT;
	return retval;
}














