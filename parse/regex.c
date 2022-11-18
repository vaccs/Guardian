
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include <assert.h>

#include <debug.h>

#include <regex/new.h>
#include <regex/clone.h>
#include <regex/dfa_to_nfa.h>
#include <regex/new_from_string.h>
#include <regex/new_from_charset.h>
#include <regex/add_lambda_transition.h>
#include <regex/free.h>

#ifdef DOTOUT
#include <regex/dotout.h>
#endif

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
					struct zebu_token* token = highest->string;
					
					dpvsn(token->data, token->len);
					
					token->len = escapes(token->data, token->len);
					
					dpvsn(token->data, token->len);
					
					retval = new_regex_from_string(token->data, token->len);
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
				regex_add_lambda_transition(retval.accepts, retval.start);
				
				struct regex* new_accepts = new_regex();
				
				regex_add_lambda_transition(retval.accepts, new_accepts);
				
				retval.accepts = new_accepts;
			}
			else if (postfix->qmark)
			{
				regex_add_lambda_transition(retval.start, retval.accepts);
			}
			else if (postfix->star)
			{
				regex_add_lambda_transition(retval.start, retval.accepts);
				regex_add_lambda_transition(retval.accepts, retval.start);
				
				struct regex* new_accepts = new_regex();
				
				regex_add_lambda_transition(retval.accepts, new_accepts);
				
				retval.accepts = new_accepts;
			}
			else if (postfix->n || postfix->m)
			{
				struct rbundle original;
				
				// convert into nfa:
				if (retval.accepts)
					original = retval;
				else
					original = regex_dfa_to_nfa(retval.start);
				
				struct limit {
					bool has;
					unsigned value;
				} min = {}, max = {};
				
				void set_limit(struct limit* l, struct zebu_token* token)
				{
					errno = 0;
					
					const char* start = (void*) token->data;
					
					char* m;
					
					unsigned long int value = strtoul(start, &m, 0);
					
					if (errno || *m)
					{
						fprintf(stderr, "zebu: error when reading grammar-rule: strtoul('%s'): %s\n", start, strerror(errno));
						exit(1);
					}
					
					l->has = true;
					l->value = value;
				}
				
				if (postfix->n)
					set_limit(&min, postfix->n);
				
				if (!postfix->c)
					max = min;
				
				if (postfix->m)
					set_limit(&max, postfix->m);
				
				if (min.has) { dpv(min.value); }
				if (max.has) { dpv(max.value); }
				
				struct regex* start = new_regex();
				
				struct regex* moving = start;
				
				unsigned i = 0;
				
				if (min.has)
				{
					for (; i < min.value; i++)
					{
						struct rbundle clone = regex_clone2(original);
						
						regex_add_lambda_transition(moving, clone.start);
						
						moving = clone.accepts;
					}
				}
				
				struct regex* accepts = new_regex();
				
				regex_add_lambda_transition(moving, accepts);
				
				if (max.has)
				{
					for (; i < max.value; i++)
					{
						struct rbundle clone = regex_clone2(original);
						
						regex_add_lambda_transition(moving, clone.start);
						
						moving = clone.accepts;
						
						regex_add_lambda_transition(moving, accepts);
					}
				}
				else
				{
					struct rbundle clone = regex_clone2(original);
					
					regex_add_lambda_transition(moving, clone.start);
					
					regex_add_lambda_transition(clone.accepts, moving);
				}
				
				retval.start = start;
				retval.accepts = accepts;
				
				#ifdef DOTOUT
				regex_dotout(retval.start, retval.accepts);
				#endif
				
				free_regex(original.start);
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














