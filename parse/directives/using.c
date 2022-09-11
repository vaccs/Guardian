
#include <debug.h>

#include <misc/break_and_open_path.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "../recursive.h"

#include "using.h"

void process_using_directive(
	struct pragma_once* pragma_once,
	int dirfd,
	struct tokenizer* tokenizer)
{
	ENTER;
	
	assert(tokenizer->token == t_using);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_string)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	char path[PATH_MAX] = {};
	
	memcpy(path, tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
	
	dpvs(path);
	
	struct br_rettype br = break_and_open_path(dirfd, path);
	
	recursive_parse(
		/* pragma_once: */ pragma_once,
		/* dirfd: */ br.dirfd,
		/* fd */ br.fd);
	
	if (br.dirfd > 0 && br.dirfd != dirfd)
		close(br.dirfd);
	
	close(br.fd);
	
	TODO;
	
	EXIT;
}









