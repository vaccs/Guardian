
#include <debug.h>

#include <regex/struct.h>
#include <regex/new.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "0.primary.h"

struct rbundle read_regex_primary_expression(
	struct tokenizer* tokenizer)
{
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character:
		{
			unsigned code = tokenizer->tokenchars.chars[0];
			
			struct regex* start = new_regex();
			struct regex* accept = new_regex();
			
			start->transitions[code] = accept;
			
			read_token(tokenizer);
			
			return (struct rbundle) {start, accept};
		}
		
		case t_string:
		{
			TODO;
			break;
		}
		
		case t_osquare:
		{
			TODO;
			break;
		}
		
		case t_oparen:
		{
			TODO;
			break;
		}
		
		default:
		{
			TODO;
			break;
		}
	}
	
	TODO;
	
	EXIT;
}
