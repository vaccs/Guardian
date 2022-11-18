
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>

#include <debug.h>

#include <gegex/new.h>
#include <gegex/clone.h>
#include <gegex/add_lambda_transition.h>
#include <gegex/free.h>

#include "../parse.h"

#include "0.highest.h"
#include "1.postfix.h"

struct gbundle read_grammar_postfix(
	struct lex* lex,
	struct zebu_grammar_postfix* postfix)
{
	ENTER;
	
	struct gbundle retval = read_grammar_highest(lex, postfix->base);
	
	if (postfix->plus)
	{
		gegex_add_lambda_transition(retval.accepts, retval.start);
		
		struct gegex* new_accepts = new_gegex();
		
		gegex_add_lambda_transition(retval.accepts, new_accepts);
		
		retval.accepts = new_accepts;
	}
	else if (postfix->qmark)
	{
		gegex_add_lambda_transition(retval.start, retval.accepts);
	}
	else if (postfix->star)
	{
		gegex_add_lambda_transition(retval.start, retval.accepts);
		gegex_add_lambda_transition(retval.accepts, retval.start);
		
		struct gegex* new_accepts = new_gegex();
		
		gegex_add_lambda_transition(retval.accepts, new_accepts);
		
		retval.accepts = new_accepts;
	}
	else if (postfix->n || postfix->m)
	{
		struct gbundle original = retval;
		
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
		
		struct gegex* start = new_gegex();
		
		struct gegex* moving = start;
		
		unsigned i = 0;
		
		if (min.has)
		{
			for (; i < min.value; i++)
			{
				struct gbundle clone = gegex_clone2(original);
				
				gegex_add_lambda_transition(moving, clone.start);
				
				moving = clone.accepts;
			}
		}
		
		struct gegex* accepts = new_gegex();
		
		gegex_add_lambda_transition(moving, accepts);
		
		if (max.has)
		{
			for (; i < max.value; i++)
			{
				struct gbundle clone = gegex_clone2(original);
				
				gegex_add_lambda_transition(moving, clone.start);
				
				moving = clone.accepts;
				
				gegex_add_lambda_transition(moving, accepts);
			}
		}
		else
		{
			struct gbundle clone = gegex_clone2(original);
			
			gegex_add_lambda_transition(moving, clone.start);
			
			gegex_add_lambda_transition(clone.accepts, moving);
		}
		
		retval.start = start;
		retval.accepts = accepts;
		
		free_gegex(original.start);
	}
	
	EXIT;
	return retval;
}

















