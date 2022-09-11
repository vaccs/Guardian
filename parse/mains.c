
#include <debug.h>

#include <misc/break_and_open_path.h>

#include "pragma_once/new.h"
#include "pragma_once/free.h"

#include "recursive.h"
#include "mains.h"

void mains_parse(const char* input_path)
{
	ENTER;
	
	dpvs(input_path);
	
	struct pragma_once* pragma_once = new_pragma_once();
	
	struct br_rettype br = break_and_open_path(AT_FDCWD, input_path);
	
	recursive_parse(
		pragma_once,
		br.dirfd,
		br.fd
	);
	
	free_pragma_once(pragma_once);
	
	if (br.dirfd > 0)
		close(br.dirfd);
	
	close(br.fd);
	
	EXIT;
}

