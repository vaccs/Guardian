
#include <debug.h>

#include <list/parameter/new.h>

#include <yacc/structinfo/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct type* new_grammar_type(
	unsigned id,
	struct string* name)
{
	ENTER;
	
	struct grammar_type* this = (void*) new_type(
		id,
		tk_grammar,
		&grammar_type_inheritance,
		sizeof(*this));
	
	this->name = inc_string(name);
	
	this->fields = new_parameter_list();
	
	EXIT;
	return (void*) this;
}

