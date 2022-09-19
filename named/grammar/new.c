
#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_grammar* new_named_grammar(
	struct string* name,
	struct gegex* grammar)
{
	ENTER;
	
	struct named_grammar* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	this->grammar = grammar;
	
	EXIT;
	return this;
}

