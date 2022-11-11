
#include <debug.h>

#include <memory/smalloc.h>

#include <set/string/inc.h>

#include "struct.h"
#include "new.h"

struct type_check_scope* new_type_check_scope(
	struct stringset* grammar_sets)
{
	ENTER;
	
	struct type_check_scope* this = smalloc(sizeof(*this));
	
	this->head = NULL;
	
	this->grammar_sets = inc_stringset(grammar_sets);
	
	EXIT;
	return this;
}

