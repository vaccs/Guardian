
#include <debug.h>

#include <yacc/structinfo/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct type* new_grammar_type(struct structinfo* structinfo)
{
	ENTER;
	
	struct grammar_type* this = (void*) new_type(
		tk_grammar,
		&grammar_type_inheritance,
		sizeof(*this));
	
	this->structinfo = inc_structinfo(structinfo);
	
	EXIT;
	return (void*) this;
}

