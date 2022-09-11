
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
		
		read_token(tokenizer);
		
		while (tokenizer->token != t_EOF)
		{
			switch (tokenizer->token)
			{
				case t_using:
				{
					process_using_directive(pragma_once, dirfd, tokenizer);
					break;
				}
				
				case t_identifier:
				{
					dpvs(tokenizer->tokenchars.chars);
					
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
























