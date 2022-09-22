
#include <debug.h>

#include <misc/break_and_open_path.h>

#include "scope/new.h"
#include "scope/free.h"

#include "pragma_once/new.h"
#include "pragma_once/free.h"

#include "recursive.h"
#include "mains.h"

void mains_parse(
	struct expressionset* assertions,
	struct avl_tree_t* grammar,
	struct type_cache* tcache,
	struct lex* lex,
	const char* input_path)
{
	ENTER;
	
	dpvs(input_path);
	
	struct scope* scope = new_scope(grammar);
	
	struct pragma_once* pragma_once = new_pragma_once();
	
	struct br_rettype br = break_and_open_path(AT_FDCWD, input_path);
	
	recursive_parse(
		assertions,
		pragma_once,
		tcache,
		scope,
		lex,
		br.dirfd,
		br.fd
	);
	
	free_pragma_once(pragma_once);
	
	free_scope(scope);
	
	if (br.dirfd > 0)
		close(br.dirfd);
	
	close(br.fd);
	
	EXIT;
}












