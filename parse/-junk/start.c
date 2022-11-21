
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <avl/insert.h>
#include <avl/search.h>

#include <gegex/free.h>

#include <gegex/combine_structinfos.h>

#include <named/grammar/new.h>

#include <named/structinfo/new.h>

#include <yacc/structinfo/free.h>

#include "grammar/3.root.h"
#include "parse.h"
#include "start.h"

void process_start(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct zebu_start_directive* directive)
{
	ENTER;
	
	EXIT;
}




