
#include <debug.h>

#include <named/type/compare.h>
#include <named/type/free.h>

#include "struct.h"
#include "new.h"

struct scope* new_scope(struct avl_tree_t* named_grammar)
{
	ENTER;
	
	struct scope* this = smalloc(sizeof(*this));
	
	this->named_grammar = named_grammar;
	
	this->named_types = avl_alloc_tree(compare_named_types, free_named_type);
	
	EXIT;
	return this;
}

