
#include <debug.h>

#include <yacc/structinfo/inc.h>

#include "../new.h"

#include "struct.h"
#include "new.h"

struct grammar_type* new_grammar_type(struct structinfo* structinfo)
{
	ENTER;
	
	struct grammar_type* this = (void*) new_type(
		tk_grammar,
		sizeof(*this));
	
	this->structinfo = inc_structinfo(structinfo);
	
	EXIT;
	return this;
}

