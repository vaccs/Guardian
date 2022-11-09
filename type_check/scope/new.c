
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct type_check_scope* new_type_check_scope(
	struct avl_tree_t* grammar_types)
{
	ENTER;
	
	struct type_check_scope* this = smalloc(sizeof(*this));
	
	this->grammar_types = grammar_types;
	
	this->head = NULL;
	
	EXIT;
	return this;
}

