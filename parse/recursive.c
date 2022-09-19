
#include <debug.h>

#include "tokenizer/struct.h"
#include "tokenizer/new.h"
#include "tokenizer/read_char.h"
#include "tokenizer/read_token.h"
#include "tokenizer/free.h"

#include "pragma_once/lookup.h"

#include "directives/skip.h"
#include "directives/start.h"
#include "directives/using.h"

#include "read_grammar_rule.h"
#include "read_value_declaration.h"
#include "recursive.h"

void recursive_parse(
	struct expressionset* assertions,
	struct pragma_once* pragma_once,
	struct type_cache* tcache,
	struct scope* scope,
	struct lex* lex,
	int dirfd, int fd)
{
	ENTER;
	
	bool first_time = pragma_once_lookup(pragma_once, fd);
	
	dpvb(first_time);
	
	if (first_time)
	{
		struct tokenizer *tokenizer = new_tokenizer(fd);
		
		read_char(tokenizer);
		
		read_token(tokenizer);
		
		while (tokenizer->token != t_EOF)
		{
			switch (tokenizer->token)
			{
				case t_directive:
				{
					char* string = (void*) tokenizer->tokenchars.chars;
					
					if (strequals(string, "%""skip"))
					{
						process_skip_directive(tokenizer, lex);
					}
					else if (strequals(string, "%""start"))
					{
						process_start_directive(tokenizer, scope, lex);
					}
					else if (strequals(string, "%""using"))
					{
						// process_directive(pragma_once, dirfd, tokenizer);
						TODO;
					}
					else
					{
						TODO;
					}
					break;
				}
				
				// grammar rule or value-define?
				case t_identifier:
				{
					dpvs(tokenizer->tokenchars.chars);
					
					struct string* name = new_string_from_tokenchars(tokenizer);
					
					dpvs(name);
					
					read_token(tokenizer);
					
					switch (tokenizer->token)
					{
						case t_colon:
							read_grammar_rule(tokenizer, tcache, scope, lex, name);
							break;
						
						case t_equals:
							read_value_declaration(tokenizer, scope, name);
							break;
						
						default:
							TODO;
							break;
					}
					
					free_string(name);
					
					break;
				}
				
				// assertion:
				case t_enforcement_level:
				{
					TODO;
					break;
				}
				
				default:
					TODO;
					break;
			}
		}
		
		free_tokenizer(tokenizer);
	}
	
	EXIT;
}
























