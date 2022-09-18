
#include <debug.h>

#include "tokenizer/struct.h"
#include "tokenizer/new.h"
#include "tokenizer/read_char.h"
#include "tokenizer/read_token.h"
#include "tokenizer/free.h"

#include "pragma_once/lookup.h"

#include "directives/using.h"

#include "recursive.h"

void recursive_parse(
	struct pragma_once* pragma_once,
	int dirfd, int fd)
{
	ENTER;
	
	bool first_time = pragma_once_lookup(pragma_once, fd);
	
	dpvb(first_time);
	
	if (first_time)
	{
		struct tokenizer *tokenizer = new_tokenizer(fd);
		
		read_char(tokenizer);
		
		TODO;
		#if 0
		read_token(tokenizer, root_machine);
		
		while (tokenizer->token != t_EOF)
		{
			switch (tokenizer->token)
			{
				case t_using:
				case t_start:
				case t_skip:
				{
					process_using_directive(pragma_once, dirfd, tokenizer);
					break;
				}
				
				// grammar rule or value-define?
				case t_identifier:
				{
					dpvs(tokenizer->tokenchars.chars);
					
					TODO;
					#if 0
					struct string* name = new_string_from_tokenchars(tokenizer);
					
					next_token(tokenizer, colon_oparen_or_equals_machine);
					
					switch (tokenizer->token)
					{
						case tk_colon:
							read_grammar_rule();
							break;
						
						case tk_equals:
							read_value_definition();
							break;
						
						default:
							TODO;
							break;
					}
					
					TODO;
					
					free_string(name);
					#endif
					
					break;
				}
				
				// assertion:
				case t_require:
				case t_warning:
				case t_info:
				case t_debug:
				{
					TODO;
					break;
				}
				
				default:
					TODO;
					break;
			}
		}
		#endif
		
		free_tokenizer(tokenizer);
	}
	
	EXIT;
}
























